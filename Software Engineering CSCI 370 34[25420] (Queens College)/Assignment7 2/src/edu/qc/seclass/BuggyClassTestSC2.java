package edu.qc.seclass;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class BuggyClassTestSC2 {


    @Test 
    public void test() throws Exception {
        BuggyClass buggy = new BuggyClass();
        try {
           buggy.buggyMethod2(10, 0, true);
           fail("Expecting a ArithmeticException to be thrown");
        }
        catch (ArithmeticException exception){
        	
        }
    }

}
