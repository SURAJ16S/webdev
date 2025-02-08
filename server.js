require("dotenv").config();
const express = require("express");
const mongoose = require("mongoose");
const jwt = require("jsonwebtoken");
const bcrypt = require("bcrypt");
const passport = require("passport");
const session = require("express-session");
const cookieParser = require("cookie-parser");
const GoogleStrategy = require("passport-google-oauth20").Strategy;
const User = require("./models/User"); // ✅ Correct path
const app = express();
require("dotenv").config();

// Middleware

app.use(express.json());
app.use(cookieParser());
app.use(
  session({
    secret: process.env.SESSION_SECRET,
    resave: false,
    saveUninitialized: true,
    cookie: { secure: false, httpOnly: true },
  })
);

app.use(passport.initialize());
app.use(passport.session());

// MongoDB Connection

mongoose
  .connect(process.env.MONGO_URI, {
    useNewUrlParser: true,
    useUnifiedTopology: true,
  })
  .then(() => console.log("✅ MongoDB Connected"))

  .catch((err) => console.log("❌ MongoDB Connection Error:", err));

// JWT Token Function

const generateToken = (user) => {
  return jwt.sign(
    { id: user._id, email: user.email },

    process.env.JWT_SECRET,
    { expiresIn: "1h" }
  );
};

// Local Signup

app.post("/signup", async (req, res) => {
  const { email, password, username } = req.body;

  const existingUser = await User.findOne({ email });

  if (existingUser)
    return res.status(400).json({ message: "User already exists" });

  const hashedPassword = await bcrypt.hash(password, 10);

  const newUser = new User({ email, username, password: hashedPassword });

  await newUser.save();

  const token = generateToken(newUser);

  res.cookie("token", token, { httpOnly: true, secure: false });

  res.json({ message: "User registered successfully", token });
});

// Local Login

app.post("/login", async (req, res) => {
  const { email, password } = req.body;

  const user = await User.findOne({ email });

  if (!user || !(await bcrypt.compare(password, user.password))) {
    return res.status(400).json({ message: "Invalid credentials" });
  }

  const token = generateToken(user);

  res.cookie("token", token, { httpOnly: true, secure: false });

  res.json({ message: "Login successful", token });
});

// Google OAuth Strategy

passport.use(
  new GoogleStrategy(
    {
      clientID: process.env.GOOGLE_CLIENT_ID,

      clientSecret: process.env.GOOGLE_CLIENT_SECRET,

      callbackURL: "/auth/google/callback",
    },
    async (accessToken, refreshToken, profile, done) => {
      let user = await User.findOne({ googleId: profile.id });

      if (!user) {
        user = new User({
          googleId: profile.id,
          email: profile.emails[0].value,
        });

        await user.save();
      }

      return done(null, user);
    }
  )
);

passport.serializeUser((user, done) => done(null, user.id));

passport.deserializeUser(async (id, done) => {
  const user = await User.findById(id);

  done(null, user);
});
// Google OAuth Routes

app.get('/auth/google', passport.authenticate('google', { scope: ['profile', 'email'] }));

  

app.get('/auth/google/callback', passport.authenticate('google', { failureRedirect: '/' }), (req, res) => {
 const token = generateToken(req.user);
 res.cookie('token', token, { httpOnly: true, secure: false });
 res.redirect('/dashboard');

});

  

// Protected Route

app.get('/dashboard', (req, res) => {
 const token = req.cookies.token;
 if (!token) return res.status(401).json({ message: 'Unauthorized' });

  
 try {
 const decoded = jwt.verify(token, process.env.JWT_SECRET);
 res.json({ message: 'Welcome to the dashboard', userId: decoded.id });
 } catch (error) {
 res.status(401).json({ message: 'Invalid Token' });
 }

});

  

// Start Server

app.listen(5000, () => console.log('🚀 Server running on port 5000'));
