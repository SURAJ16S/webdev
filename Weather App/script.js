document.addEventListener('DOMContentLoaded', () => {
    //collect evrything from the html
     const cityInput = document.getElementById('city-input');
     const getWeatherbtn = document.getElementById('get-weather-btn');
     const weatherInfo = document.getElementById('weather-info');
     const cityNameDisplay = document.getElementById('city-name');
     const temperatureDisplay = document.getElementById('temperature');
     const descriptionDisplay = document.getElementById('description');
     const errorMessage = document.getElementById("error-message");
     //store the api key in the variable
     const API_KEY = "Enter Your Api KEY Here From Open Weather"; //env _variables
 
     getWeatherbtn.addEventListener('click', async () => { // Added 'async' here
         const city = cityInput.value.trim(); //trim remove the spaces
         if (!city) return;
         //now we will make the web request
         try {
             const weatherData = await fetchWeatherData(city); // Added 'await' here
             displayWeatherData(weatherData);
         } catch {
             showError();
         }
     });
     //*whenever you are making a web request to any other server or database - 1) server may throuw you some error , 2) server is always or database is always in another continent so it requires some time : 
     //so we have to handle these two cases
     //fetch is a function that is used to make a web request
     //fetch is a promise based function
     //fetch returns a promise
 
     //to receive the error use the try catch block
     async function fetchWeatherData(city) {
         //gets the data
         const url = `https://api.openweathermap.org/data/2.5/weather?q=${city}&appid=${API_KEY}`;
 
         const response = await fetch(url);
         console.log(typeof response);
         console.log(response);
 
         if (!response) {
             throw new Error('City Not Found');
         }
         const data = await response.json();
         return data;    
     }
     function displayWeatherData(data) {
         //display the data
         const { name, main, weather } = data;
         cityNameDisplay.textContent = name;
         console.log(data);
//how to round of the temperature

        temperatureDisplay.textContent = `Temperature: ${(main.temp - 273.15).toFixed(2)}°C`;
         descriptionDisplay.textContent = weather[0].description;
         //unlock the display
         weatherInfo.classList.remove('hidden');
         errorMessage.classList.add('hidden');
     }
     function showError() {
         //display the error
         weatherInfo.classList.add('hidden');
         errorMessage.classList.remove('hidden');
     }
 });
