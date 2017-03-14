import static org.junit.Assert.*;
import org.junit.Before;
import org.junit.Test;

public class BankAccountTest {
    static double interest1 = -1;
    static double interest2 = -1;
    static double interest3 = -1;
    static double interest4 = -1 ;
    static boolean isSetup = false;
    public boolean isAccountNumberValid(int number) {
        return number >= 100000 && number < 1000000;
    }

    public boolean doubleEqual(double d1, double d2) {
        return Math.abs(d1 - d2) < 0.01;
    }

    @Before
    public void setUp() {
        if (this.isSetup)
        {
            return;
        }

        else
        {
            this.isSetup = true;
            //the code for test interest
            if (interest1 < 0){
                interest1 = BankAccount.getInterestRate();
            }
            BankAccount aa1;
            aa1 = new BankAccount("a1");

            BankAccount aa2;
            aa2 = new BankAccount("a2");

            BankAccount aa3;
            aa3 = new BankAccount("a3");

            BankAccount aa4;
            aa4 = new BankAccount("a4");

            BankAccount aa5;
            aa5 = new BankAccount("a5");

            if (interest2 < 0) {
                interest2 = BankAccount.getInterestRate();
            }

            BankAccount aa7;
            aa7 = new BankAccount("a11");

            BankAccount aa8;
            aa8 = new BankAccount("a21");

            BankAccount aa9;
            aa9 = new BankAccount("a31");

            BankAccount aa10;
            aa10 = new BankAccount("a41");

            BankAccount aa11;
            aa11 = new BankAccount("a51");

            if (interest3 < 0) {
                interest3 = BankAccount.getInterestRate();
            }

            BankAccount ba1;
            ba1 = new BankAccount("a21");

            BankAccount ba2;
            ba2 = new BankAccount("a22");

            BankAccount ba3;
            ba3= new BankAccount("a23");

            BankAccount ba4;
            ba4= new BankAccount("a24");

            BankAccount ba5;
            ba5= new BankAccount("a25");

            if (interest4 < 0) {
                interest4 = BankAccount.getInterestRate();
            }
        }

    }


    @Test
    public void testInterest00() {
        assertTrue("Error with interestRate", doubleEqual(interest1, 0.30));
    }

    @Test
    public void testInterest01() {
        assertTrue("Error with interestRate", doubleEqual(interest2, 0.28));

    }

    @Test
    public void testInterest02() {
        assertTrue("Error with interestRate", doubleEqual(interest3, 0.26));
    }

    @Test
    public void testInterest03() {
        assertTrue("Error with interestRate", doubleEqual(interest4, 0.24));
    }

    @Test
    public void testConstructor00() {
        BankAccount a1;
        a1 = new BankAccount("Bob");
        assertTrue("Error with account number ", isAccountNumberValid(a1.getAccountNumber()));
    }
    @Test
    public void testConstructor01() {
        BankAccount a1;
        a1 = new BankAccount("Bob", 0);
        a1 = new BankAccount("Bob", 100);

        assertTrue("Error with account number ", isAccountNumberValid(a1.getAccountNumber()));
    }


    @Test
    public void testAccountNumber00() {
        BankAccount a1;
        a1 = new BankAccount("Bob");
        assertTrue("Error with account number ", isAccountNumberValid(a1.getAccountNumber()));

    }

    @Test
    public void testAccountNumber01() {
        BankAccount a1;
        a1 = new BankAccount("Carl");
        assertTrue("Error with account number ", isAccountNumberValid(a1.getAccountNumber()));

    }




    @Test
    public void testWithdrawMoney00() {
        BankAccount a1;
        a1 = new BankAccount("a1", 0);
        a1 = new BankAccount("a1", 100);
        assertTrue("Error with withdraw ", doubleEqual(80, a1.withdrawMoney(80)));
    }

    @Test
    public void testWithdrawMoney01() {
        BankAccount a1;
        a1 = new BankAccount("a1", 0);
        a1 = new BankAccount("a1", 150);
        assertTrue("Error with withdraw ", doubleEqual(-1, a1.withdrawMoney(200)));
    }

    @Test
    public void testDeposit00() {
        BankAccount a1;
        a1 = new BankAccount("a2", 0);
        a1 = new BankAccount("a2", 150);
        assertTrue("Error with deposit ", doubleEqual(135, a1.deposit(135)));
    }

    @Test
    public void testDeposit01() {
        BankAccount a1;
        a1 = new BankAccount("a2", 0);
        a1 = new BankAccount("a2", 100);
        assertTrue("Error with deposit", doubleEqual(-1, a1.deposit(-100)));
    }

    @Test
    public void testTransfer00() {
        BankAccount a1;
        a1 = new BankAccount("a1", 0);
        a1 = new BankAccount("a1", 100);

        BankAccount a2;
        a2 = null;
        assertTrue("Error with transfer" , doubleEqual(-1, a1.transfer(a2, 50)));
    }


    @Test
    public void testTransfer01() {
        BankAccount a1;
        a1 = new BankAccount("a1", 0);
        a1 = new BankAccount("a1", 100);

        BankAccount a2;
        a2 = new BankAccount("a2", 0);
        a2 = new BankAccount("a2", 100);
        assertTrue("Error with transfer" , doubleEqual(-1, a1.transfer(a2, 300)));
    }

    @Test
    public void testTransfer02() {
        BankAccount a1;
        a1 = new BankAccount("a1", 0);
        a1 = new BankAccount("a1", 150);

        BankAccount a2;
        a2 = new BankAccount("a1", 0);
        a2 = new BankAccount("a2", 50);
        assertTrue("Error with transfer" , doubleEqual(50, a1.transfer(a2, 50)));
    }



    @Test
    public void testTransfer03() {
        BankAccount a1;
        a1 = new BankAccount("a1", 0);
        a1 = new BankAccount("a1", 100);

        BankAccount a2;
        a2 = new BankAccount("a2", 0);
        a2 = new BankAccount("a2", 20);
        assertTrue("Error with transfer to account" , doubleEqual(-1, a1.transfer(a2, -50)));
    }
    @Test
    public void testMultipleTransfer00() {
        BankAccount a1;
        a1 = new BankAccount("a1", 0);
        a1 = new BankAccount("a1", 100);

        BankAccount[] a2;
        a2 = null;
        assertTrue("Error with transfer to account" , doubleEqual(-1, a1.transfer(a2, 50)));
    }

    @Test
    public void testMultipleTransfer01() {
        BankAccount a1;
        a1 = new BankAccount("a1", 0);
        a1 = new BankAccount("a1", 100);

        BankAccount[] a2 = {};
        assertTrue("Error with transfer to accounts" , doubleEqual(-1, a1.transfer(a2, 50)));
    }

    @Test
    public void testMultipleTransfer02() {
        BankAccount a1;
        a1 = new BankAccount("a1", 0);
        a1 = new BankAccount("a1", 100);

        BankAccount a2;
        a2 = new BankAccount("a2", 0);
        a2 = new BankAccount("a2", 20);

        BankAccount a3;
        a3 = new BankAccount("a3", 0);
        a3 = new BankAccount("a3", 40);

        BankAccount[] accounts = {a2, a3};

        assertTrue("Error with transfer to accounts" , doubleEqual(-1, a1.transfer(accounts, 60)));
    }

    @Test
    public void testMultipleTransfer03() {
        BankAccount a1;
        a1 = new BankAccount("a1", 100);

        BankAccount a2;
        a2 = new BankAccount("a2", 20);

        BankAccount a3;
        a3 = new BankAccount("a3", 40);

        BankAccount[] accounts = {a2, a3};

        double returnValue = a1.transfer(accounts, 50);
        assertTrue("Error with transfer to accounts" + returnValue, doubleEqual(100, returnValue));
    }

}