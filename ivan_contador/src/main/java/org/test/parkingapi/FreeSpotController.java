package org.test.parkingapi;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import java.util.List;
import java.util.Optional;
//RestController para que responda peticiones como GET o POST
@RestController
@CrossOrigin(origins = "*")
public class FreeSpotController {

    @Autowired
    private ParkingSpotRepository repository;

    // ==============================================================
    // ENDPOINTS NUEVOS (Postman / ESP32)
    // ==============================================================
    //funcion que respondera cuando alguien haga una peticion GET
    //llama a getAllSpots y devuelve las plazas totales
    //find all para que lea la tabla de plazas en mySQL
    @GetMapping("/api/parking")
    public List<ParkingSpot> getAllSpots() {
        return repository.findAll(); // Lee de MySQL
    }
//esta funcion responde a peticiones POST este cogera un JSON y lo convertira en un objeto    @PostMapping("/api/parking")
//Buscara en la base de datos con el mismo id que el recibido
//si existe la actualizara si no lo guarda
    public ParkingSpot updateSpot(@RequestBody ParkingSpot spot) {
        Optional<ParkingSpot> existing = repository.findById(spot.getId());
        if (existing.isPresent()) {
            ParkingSpot toUpdate = existing.get();
            toUpdate.setFree(spot.isFree());
            if (spot.getZone() != null) {
                toUpdate.setZone(spot.getZone());
            }
            return repository.save(toUpdate); // Actualiza en MySQL
        } else {
            return repository.save(spot); // Guarda una plaza nueva en MySQL
        }
    }

    // ==============================================================
    // ENDPOINTS ORIGINALES (Para tu página web Nginx)
    // ==============================================================
    @GetMapping("/freespot")
    public int getFreeSpotsCount() {
        return repository.countByFreeTrue();
    }

    @GetMapping("/freespot/zoneA")
    public int getZoneCountA() {
        return repository.countByZoneAndFreeTrue("A");
    }

    @GetMapping("/freespot/zoneB")
    public int getZoneCountB() {
        return repository.countByZoneAndFreeTrue("B");
    }

    @GetMapping("/freespot/zoneC")
    public int getZoneCountC() {
        return repository.countByZoneAndFreeTrue("C");
    }
}
