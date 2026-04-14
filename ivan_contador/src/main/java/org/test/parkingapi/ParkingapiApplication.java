package org.test.parkingapi;

import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

@SpringBootApplication
public class ParkingapiApplication {

    public static void main(String[] args) {
        SpringApplication.run(ParkingapiApplication.class, args);
    }

    // Este código se ejecuta nada más arrancar la aplicación
    @Bean
    public CommandLineRunner initData(ParkingSpotRepository repository) {
        return args -> {
            // Si la base de datos está vacía, mete las 5 plazas iniciales
            if (repository.count() == 0) {
                repository.save(new ParkingSpot(1, "A", true));
                repository.save(new ParkingSpot(2, "B", false));
                repository.save(new ParkingSpot(3, "C", true));
                repository.save(new ParkingSpot(4, "A", false));
                repository.save(new ParkingSpot(5, "B", true));
                System.out.println("Plazas iniciales inyectadas en MySQL.");
            }
        };
    }
}
