google.maps.visualRefresh = true;

var map;
var lat = 34.2005;
var long = -118.1734;
var myLatlng = new google.maps.LatLng(lat, long);
var newLatlng = new google.maps.LatLng(lat + 0.0001, long + 0.0001);

function initialize() {
    var myOptions = {
        zoom: 30,
        center: myLatlng,
        mapTypeId: google.maps.MapTypeId.HYBRID,
        zoomControl: true,
        zoomControlOptions: { style: google.maps.ZoomControlStyle.SMALL },
    };

    map = new google.maps.Map(document.getElementById('map_canvas'), myOptions);
    var marker_1 = new google.maps.Marker({
        position: myLatlng,
        map: map,
        title:"current"
    });

    var polyOptions = {
        strokeColor: '#000000',
        strokeOpacity: 1.0,
        strokeWeight: 3
      };
      poly = new google.maps.Polyline(polyOptions);
      poly.setMap(map);

      // Add a listener for the click event
      google.maps.event.addListener(map, 'click', addLatLng);
}

/**
 * Handles click events on a map, and adds a new point to the Polyline.
 * @param {google.maps.MouseEvent} event
 */
function addLatLng(event) {

    var path = poly.getPath();

    // Because path is an MVCArray, we can simply append a new coordinate
    // and it will automatically appear.
    path.push(event.latLng);

    // Add a new marker at the new plotted point on the polyline.
    var marker = new google.maps.Marker({
        position: event.latLng,
        title: '#' + path.getLength(),
        map: map
    });
}


google.maps.event.addDomListener(window, 'load', initialize);
