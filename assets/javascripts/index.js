const map = L.map('map', {
    center: [-40.81096158981925, 173.95225110400173],
    zoom: 3.5
});

L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
}).addTo(map);

// Replace 'YOUR_API_KEY' with your actual OpenWeatherMap API key
const apiKey = 'cd6160f091b27addb4600525abbcf0f2';
-45.883268013958514, 170.49907238856377
// Get the weather data for the center of your map
fetch(`https://api.openweathermap.org/data/2.5/weather?lat=${-45.883268013958514}&lon=${170.49907238856377}&units=metric&appid=${apiKey}`)
    .then(response => response.json())
    .then(data => {
        // Extract relevant weather information
        const temperature = data.main.temp;
        const weatherDescription = data.weather[0].description;
        console.log(`Temperature: ${temperature}°C`);
        console.log(`Weather: ${weatherDescription}`);
        // Create a marker with a popup displaying weather information
        const marker = L.marker([-45.883268013958514, 170.49907238856377]).addTo(map);
        marker.bindPopup(`Temperature: ${temperature}&#8451;<br>Weather: ${weatherDescription}`).openPopup();
    })
    .catch(error => {
        console.error('Error fetching weather data:', error);
    });
