/**
 * Created by sidshah on 3/1/17.
 */
public class FighterJet implements Vehicle{
    private String name;
    private int maxPassengers;
    private int maxSpeed;
    private int numWheels;
    private String startEngine;
    private boolean canFly;

    public FighterJet(){
        this.name = "F-15";
        this.maxPassengers = 2;
        this.maxSpeed = 1875;
        this.numWheels = 3;
        this.startEngine = "Whoosh!";
        this.canFly = true;
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

    public String sonicBoom(int currentSpeed){
        if(currentSpeed > 761){
            return "BOOM!";
        }
        else{
            return "Whoosh!";
        }
    }
}
