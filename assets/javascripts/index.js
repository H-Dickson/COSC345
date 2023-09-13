
const map = L.map('map',
{
    center: [-40.81096158981925, 173.95225110400173],
    zoom: 3.5

    });

L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
      

      
      
    attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
}).addTo(map);
var latlngs = [[20, 20], [-20, 20], [-20, -20]];
var marker = L.marker([20, 20]).addTo(map);
