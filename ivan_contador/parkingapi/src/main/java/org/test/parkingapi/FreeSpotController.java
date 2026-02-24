package org.test.parkingapi;

import org.springframework.web.bind.annotation.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@RestController
@CrossOrigin(origins = "*")
public class FreeSpotController {

    // Lista global y modificable en memoria (simulando base de datos)
    private List<ParkingSpot> spots = new ArrayList<>(Arrays.asList(
            new ParkingSpot(1, "A", true),
            new ParkingSpot(2, "B", false),
            new ParkingSpot(3, "C", true),
            new ParkingSpot(4, "A", false),
            new ParkingSpot(5, "B", true)
    ));

    // ==============================================================
    // ENDPOINTS NUEVOS (Para usar con Postman y el ESP32)
    // ==============================================================

    // Ver todas las plazas y su estado (GET http://IP:8080/api/parking)
    @GetMapping("/api/parking")
    public List<ParkingSpot> getAllSpots() {
        return spots;
    }

    // Actualizar si una plaza está ocupada o libre (POST http://IP:8080/api/parking)
    @PostMapping("/api/parking")
    public ParkingSpot updateSpot(@RequestBody ParkingSpot spot) {
        for (ParkingSpot existingSpot : spots) {
            if (existingSpot.getId() == spot.getId()) {
                existingSpot.setFree(spot.isFree());
                // Solo actualizamos la zona si se envía en el JSON
                if (spot.getZone() != null) {
                    existingSpot.setZone(spot.getZone());
                }
                return existingSpot;
            }
        }
        // Si la plaza no existe, la añade a la lista
        spots.add(spot);
        return spot;
    }

    // ==============================================================
    // ENDPOINTS ORIGINALES (Para tu página web Nginx / Parking ASIX)
    // ==============================================================

    @GetMapping("/freespot")
    public int getFreeSpotsCount() {
        int freeCount = 0;
        for (ParkingSpot spot : spots) {
            if (spot.isFree()) {
                freeCount++;
            }
        }
        return freeCount;
    }

    @GetMapping("/freespot/zoneA")
    public int getZoneCountA() {
        int counterZoneA = 0;
        for (ParkingSpot spot : spots) {
            if(spot.getZone().equals("A") && spot.isFree()) {
                counterZoneA++;
            }
        }
        return counterZoneA;
    }

    @GetMapping("/freespot/zoneB")
    public int getZoneCountB() {
        int counterZoneB = 0;
        for (ParkingSpot spot : spots) {
            if(spot.getZone().equals("B") && spot.isFree()) {
                counterZoneB++;
            }
        }
        return counterZoneB;
    }

    @GetMapping("/freespot/zoneC")
    public int getZoneCountC() {
        int counterZoneC = 0;
        for (ParkingSpot spot : spots) {
            if(spot.getZone().equals("C") && spot.isFree()) {
                counterZoneC++;
            }
        }
        return counterZoneC;
    }
}
