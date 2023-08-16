#include <TinyGPS++.h>
#include <SoftwareSerial.h>

const int GPS_TX_PIN = 4; // GPS TX pin connected to NodeMCU D4 pin
const int GPS_RX_PIN = 3; // GPS RX pin connected to NodeMCU D5 pin

SoftwareSerial gpsSerial(GPS_TX_PIN, GPS_RX_PIN);
TinyGPSPlus gps;

double prevLatitude = 0.0;
double prevLongitude = 0.0;
double totalDistance = 0.0;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
}

double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
  double rlat1 = radians(lat1);
  double rlon1 = radians(lon1);
  double rlat2 = radians(lat2);
  double rlon2 = radians(lon2);

  double dlon = rlon2 - rlon1;
  double dlat = rlat2 - rlat1;

  double a = pow(sin(dlat / 2), 2) + cos(rlat1) * cos(rlat2) * pow(sin(dlon / 2), 2);
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));

  const double radius = 6371000; // Earth's radius in meters
  double distance = radius * c;

  return distance;
}

void loop() {
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        double latitude = gps.location.lat();
        double longitude = gps.location.lng();

        if (prevLatitude != 0.0 && prevLongitude != 0.0) {
          double distance = calculateDistance(prevLatitude, prevLongitude, latitude, longitude);
          totalDistance += distance;
        }

        prevLatitude = latitude;
        prevLongitude = longitude;

        Serial.print("Latitude: ");
        Serial.print(latitude, 6);
        Serial.print(", Longitude: ");
        Serial.print(longitude, 6);
        Serial.print(", Distance (meters): ");
        Serial.println(totalDistance);
      } else {
        Serial.println("GPS data not available.");
      }
    }
  }
}
