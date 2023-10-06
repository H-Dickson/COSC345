const map = L.map('map', {
    center: [-40.81096158981925, 173.95225110400173],
    zoom: 3.5
});

const apiKey = 'cd6160f091b27addb4600525abbcf0f2';
L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
}).addTo(map);

let markers = [];
let clickedPoints = [];

map.on('click', function (e) {
    const lat = e.latlng.lat;
    const long = e.latlng.lng;
    console.log("Testing C++ to JS");
    try{
        const C_Value = GetArea(lat, long);
        console.log(C_Value);
    }catch{
        console.error("Error fetching area", error);
    }
    // Clear previous markers and route
    markers.forEach(marker => map.removeLayer(marker));
    markers = [];
    if (clickedPoints.length >= 2) {
        map.removeControl(routeControl);
        clickedPoints = [];
    }

    fetch(`https://api.openweathermap.org/data/2.5/weather?lat=${lat}&lon=${long}&units=metric&appid=${apiKey}`)
        .then(response => response.json())
        .then(data => {
            const temperature = data.main.temp;
            const weatherDescription = data.weather[0].description;

            const marker = L.marker([lat, long]).addTo(map);
            marker.bindPopup(`Temperature: ${temperature}&#8451;<br>Weather: ${weatherDescription}`).openPopup();

            markers.push(marker);
            clickedPoints.push({ lat, lng: long, temperature, weatherDescription });

            if (clickedPoints.length === 2) {
                createRoute(clickedPoints[0], clickedPoints[1]);
            }
        })
        .catch(error => {
            console.error('Error fetching weather data:', error);
        });
});

let routeControl = null;

function createRoute(start, end) {
    routeControl = L.Routing.control({
        waypoints: [
            L.latLng(start.lat, start.lng),
            L.latLng(end.lat, end.lng)
        ],
        routeWhileDragging: true
    }).addTo(map);
}
