package edu.qc.seclass;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class BuggyClassTestBC3 {

	@Test
	void test() {
        BuggyClass buggy = new BuggyClass();
        try {
            buggy.buggyMethod3(2, 1);
            fail("expecting an ArithmeticException to be thrown");
        } catch (ArithmeticException e) {
         
        }
	}

}
