/**
 * Created by sidshah on 3/1/17.
 */
public class OilTanker implements Vehicle {
    private String name;
    private int maxPassengers;
    private int maxSpeed;
    private int numWheels;
    private String startEngine;
    private boolean canFly;

    public OilTanker(){
        this.name = "Oil Tanker";
        this.maxPassengers = 30;
        this.maxSpeed = 20;
        this.numWheels = 0;
        this.startEngine = "Brum Brum!";
        this.canFly = false;
    }
    public String name(){
        return this.name;
    }

    public int maxPassengers(){
        return this.maxPassengers;
    }

    public int maxSpeed(){
        return this.maxSpeed;
    }

    public int numWheels(){
        return this.numWheels;
    }

    public String startEngine(){
        return this.startEngine;
    }

    public boolean canFly(){
        return this.canFly;
    }

    public double maxOilCarried(double radius, double height){
        return Math.PI * (radius * radius) * height;
    }
}
