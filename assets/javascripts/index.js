const map = L.map('map', {
    center: [-40.81096158981925, 173.95225110400173],
    zoom: 3.5
});

L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
}).addTo(map);

// Replace 'YOUR_API_KEY' with your actual OpenWeatherMap API key
const apiKey = 'cd6160f091b27addb4600525abbcf0f2';
let markers = []; // Array to store markers
fetch(`https://api.openweathermap.org/data/2.5/weather?lat=${-45.88473775220725}&lon=${170.49865523171846}&units=metric&appid=${apiKey}`)
    .then(response => response.json())
    .then(data => {
        // Extract relevant weather information
        const temperature = data.main.temp;
        const weatherDescription = data.weather[0].description;
        
        // Create a marker with a popup displaying weather information
        const marker = L.marker([-45.88473775220725, 170.49865523171846]).addTo(map);
        marker.bindPopup(`Temperature: ${temperature}&#8451;<br>Weather: ${weatherDescription}`).openPopup();
        markers.push(marker); // Add the new marker to the array
        setupCommunication(temperature, weatherDescription);
    })
    .catch(error => {
        console.error('Error fetching weather data:', error);
    });
    


function onMapClick(e) {
    var latlng = e.latlng.toString()
    latlng = latlng.substring(7, latlng.length - 1)
    const resultArray = splitStringAtCommaSpace(latlng);
    lat = resultArray[0]
    long = resultArray[1]

    // Remove markers if there are more than two
    if (markers.length >= 2) {
        const removedMarker = markers.pop(); // Remove the oldest marker
        map.removeLayer(removedMarker); // Remove it from the map
    }

    fetch(`https://api.openweathermap.org/data/2.5/weather?lat=${lat}&lon=${long}&units=metric&appid=${apiKey}`)
        .then(response => response.json())
        .then(data => {
            // Extract relevant weather information
            const temperature = data.main.temp;
            const weatherDescription = data.weather[0].description;
            console.log(`Temperature: ${temperature}°C`);
            console.log(`Weather: ${weatherDescription}`);

            // Create a marker with a popup displaying weather information
            const marker = L.marker([lat, long]).addTo(map);
            marker.bindPopup(`Temperature: ${temperature}&#8451;<br>Weather: ${weatherDescription}`).openPopup();

            markers.push(marker); // Add the new marker to the array
        })
        .catch(error => {
            console.error('Error fetching weather data:', error);
        });
}

map.on('click', onMapClick);

function splitStringAtCommaSpace(inputString) {
    return inputString.split(', ');
}
function setupCommunication(temp,weather) {
    // This function is called when the DOM is ready
    // You can call HandleWeatherData with data from JavaScript
    var temperature = temp;
    var weatherDescription = weather;
    handleWeatherData(temperature, weatherDescription);
}
function receiveDataFromCpp(temperature, weatherDescription) {
    // Handle the data received from C++
    console.log(temperature);
    console.log(weatherDescription);
    // Perform JavaScript logic with the data
}