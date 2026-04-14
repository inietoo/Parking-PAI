package org.test.parkingapi;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

@Entity
@Table(name = "parking_spots") // Nombre de la tabla en MySQL
public class ParkingSpot {

    @Id
    private int id; // El ID será la clave primaria (Primary Key)

    private String zone;
    private boolean free;

    // IMPORTANTE: JPA necesita un constructor vacío
    public ParkingSpot() {
    }

    public ParkingSpot(int id, String zone, boolean free) {
        this.id = id;
        this.zone = zone;
        this.free = free;
    }

    public int getId() { return id; }
    public void setId(int id) { this.id = id; }

    public String getZone() { return zone; }
    public void setZone(String zone) { this.zone = zone; }

    public boolean isFree() { return free; }
    public void setFree(boolean free) { this.free = free; }
}
