package org.test.parkingapi;


public class ParkingSpot {
    //Aqui esoy creando las variables que usaremos mas adelante
private int id;
private String zone;
private boolean free;

public ParkingSpot(int id, String zone, boolean free) {
    this.id = id;
    this.zone = zone;
    this.free = free;
}
public int getId() {
    return id;
}
public String getZone() {
    return zone;
}
public boolean isFree() {
    return free;
}
}
