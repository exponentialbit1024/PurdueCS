import java.util.ArrayList;
import java.util.Random;


public class BankAccount {
    //instance variables
    private int accountNumber;
    private String name;
    private double balance;

    //static properties
    private static double interest = 0.3;
    private static ArrayList<BankAccount> accounts = new ArrayList<BankAccount>();

    //The first constructor receives a name and creates bank account with balance = 0
    public  BankAccount (String name) {
        this.name = name;
        this.balance = 0;
        Random rand = new Random();
        this.accountNumber = rand.nextInt(1000000 - 100000 + 1) + 99999;
        this.accounts.add(this);
    }

    //The second constructor receives name and balance, creates a bank amount and updates balance
    public BankAccount (String name, double balance) {
        this.name = name;
        this.balance = balance;
        Random rand = new Random();
        this.accountNumber = rand.nextInt(1000000 - 100000 + 1) + 100000;
        this.accounts.add(this);
    }

    //This method performs deposit operation
    public double deposit(double money) {
        if(money < 0){
            return -1;
        }
        this.balance += money;
        return money;
    }

    //This method performs withdraw operation
    public double withdrawMoney(double money) {
        if(money > this.balance){
            return -1;
        }
        if(money < 0){
            return -1;
        }
        this.balance -= money;
        return money;
    }

    //This method returns account number
    public int getAccountNumber() {
        return this.accountNumber;
    }

    //This method returns interest rate
    public static double getInterestRate() {
        double tempInt = BankAccount.interest - (accounts.size() / 5) * 0.02;
        return tempInt;
    }

    //This method performs a transfer operation to a single bank account
    public double transfer(BankAccount destinationBankAccount, double amount) {
        if(destinationBankAccount == null){
            return -1;
        }
        double withdrawSuc = this.withdrawMoney(amount);
        if((int)withdrawSuc == -1){
            return -1;
        }
        if(amount < 0){
            return -1;
        }
        destinationBankAccount.deposit(amount);
        return amount;
    }

    //This method performs a transfer operation to multiple accounts
    public double transfer(BankAccount[] destinationBankAccount, double amount) {
        if(destinationBankAccount == null){
            return -1;
        }
        if(destinationBankAccount.length == 0){
            return -1;
        }

        for(int i = 0; i < destinationBankAccount.length; i++){
            if(destinationBankAccount[i] == null){
                return -1;
            }
            if(this.balance < amount){
                return -1;
            }
            this.balance -= amount;
            destinationBankAccount[i].balance += amount;
        }
        return amount * destinationBankAccount.length;
    }

    public static void main(String args[]) {
        //Feel free to add code that will help you test your methods
    }
}