package org.test.parkingapi;

public class SensorUpdate {
    private int spotId;
    private String zone;
    private boolean free;
    public SensorUpdate(int spotId, String zone, boolean free){

    }
    public SensorUpdate(){}
    public String getZone() {
        return zone;
    }

    public void setZone(String zone) {
        this.zone = zone;
    }

    public int getSpotId() {
        return spotId;
    }

    public void setSpotId(int spotId) {
        this.spotId = spotId;
    }

    public boolean isFree() {
        return free;
    }

    public void setFree(boolean free) {
        this.free = free;
    }
}
