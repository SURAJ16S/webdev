const mongoose = require("mongoose");

const UserSchema = new mongoose.Schema({
  username: { type: String, required: true, unique: true },

  email: { type: String, required: true, unique: true }, // We have Added email

  password: { type: String },

  googleId: { type: String, unique: true }, //  We Have Added googleId for Google OAuth
});

module.exports = mongoose.model("User", UserSchema);
