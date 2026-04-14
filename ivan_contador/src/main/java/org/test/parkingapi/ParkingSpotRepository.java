package org.test.parkingapi;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface ParkingSpotRepository extends JpaRepository<ParkingSpot, Integer> {

    // Spring Boot crea la consulta SQL automáticamente solo con leer el nombre del método:
    int countByFreeTrue();
    int countByZoneAndFreeTrue(String zone);
}
