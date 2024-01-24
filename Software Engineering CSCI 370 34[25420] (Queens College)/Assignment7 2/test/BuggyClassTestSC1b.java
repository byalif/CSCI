package edu.qc.seclass;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class BuggyClassTestSC1b {

	@Test
	void test() {
		//Less then 50% coverage because the first statement throws exception
		BuggyClass buggy = new BuggyClass();
		IllegalArgumentException exception = assertThrows(IllegalArgumentException.class, () -> buggy.buggyMethod1(15, 0));
		assertEquals("Argument 'divisor' is 0", exception.getMessage());
	}
}
