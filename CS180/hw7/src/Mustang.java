/**
 * Created by sidshah on 3/1/17.
 */
public class Mustang implements Vehicle {
    private String name;
    private int maxPassengers;
    private int maxSpeed;
    private int numWheels;
    private String startEngine;
    private boolean canFly;

    public Mustang(){
        this.name = "Mustang";
        this.maxPassengers = 4;
        this.maxSpeed = 180;
        this.numWheels = 4;
        this.startEngine = "Vroom Vroom!";
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
}
