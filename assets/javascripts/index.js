const map = L.map('map', {
    //center: [57.74, 11.94],
    center: [-40.81096158981925, 173.95225110400173],
    zoom: 3.5
});
const apiKey = 'cd6160f091b27addb4600525abbcf0f2';
L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
}).addTo(map);

let markers = [];



let previousMarker = null; // To store the previous clicked marker

/*
map.on('click', function (e) {
    const lat = e.latlng.lat;
    const long = e.latlng.lng;

    if (markers.length >= 2) {
        const removedMarker = markers.pop();
        map.removeLayer(removedMarker);
    }

    fetch(`https://api.openweathermap.org/data/2.5/weather?lat=${lat}&lon=${long}&units=metric&appid=${apiKey}`)
        .then(response => response.json())
        .then(data => {
            const temperature = data.main.temp;
            const weatherDescription = data.weather[0].description;

            const marker = L.marker([lat, long]).addTo(map);
            marker.bindPopup(`Temperature: ${temperature}&#8451;<br>Weather: ${weatherDescription}`).openPopup();

            markers.push(marker);
            createPath(e.latlng, marker.getLatLng());
        })
        .catch(error => {
            console.error('Error fetching weather data:', error);
        });
});*/
L.Routing.control({
    waypoints: [
        L.latLng(-45.87449754029905, 170.50337550746337),
        L.latLng(-45.09709116137747, 170.97129551312722)
    ],
    routeWhileDragging: true
}).addTo(map);