package org.test.parkingapi;

import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.Arrays;
import java.util.List;

//anotacion para indicar que este codigo devuelve HTTP
@RestController
@CrossOrigin(origins = "*")
public class FreeSpotController {
    //GetMapping esta indicando que cuando llegue una peticion Get en la ruta /hello devolvera el mensaje de debajo
    @GetMapping("/freespot")
    public int getFreeSpotsCount() {
        // Misma lista de antes (luego la moveremos a un servicio)
        List<ParkingSpot> spots = Arrays.asList(
                new ParkingSpot(1, "A", true),
                new ParkingSpot(2, "B", false),
                new ParkingSpot(3, "C", true)
        );

        int freeCount = 0;
        for (ParkingSpot spot : spots) {
            if (spot.isFree()) {
                freeCount++;
            }
        }

        return freeCount;
    }
    //Aqui estoy creando las listas para hacer pruebas
    public List<ParkingSpot> getFreeSpots() {
        List<ParkingSpot> spots = Arrays.asList(
                new ParkingSpot(1, "A", true),
                new ParkingSpot(2, "B", false),
                new ParkingSpot(3, "C", true)
        );

        return spots;
    }
    //creamos este get para cuando reciba la peticion para saber las plazas de la zonaA las devuelva
    @GetMapping("freespot/zoneA")
    public int getZoneCountA(){
        //inicializamos el contador en 0
        int counterZoneA = 0;
        //Recuperamos las listas para saber las plazas
        getFreeSpots();
        //bucle For para saber las plazas libres
        for (ParkingSpot spot : getFreeSpots()) {
            //condicional si la zona equivale a A y el espacio esta libre suma
            if(spot.getZone().equals("A") && spot.isFree()){
                counterZoneA++;
            }
        }
        return counterZoneA;
    }

    @GetMapping("freespot/zoneB")
    public int getZoneCountB(){
        int counterZoneB = 0;
        getFreeSpots();
        for (ParkingSpot spot : getFreeSpots()) {
            if(spot.getZone().equals("B") && spot.isFree()){
                counterZoneB++;
            }
        }
        return counterZoneB;
    }

    @GetMapping("freespot/zoneC")
    public int getZoneCountC(){
        int counterZoneC = 0;
        getFreeSpots();
        for (ParkingSpot spot : getFreeSpots()) {
            if(spot.getZone().equals("C") && spot.isFree()){
                counterZoneC++;
            }
        }
        return counterZoneC;
    }
}

