package edu.qc.seclass;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class BuggyClassTestSC1a {

	@Test
	void test() {
		//100% coverage because it will use all statements
		BuggyClass buggy = new BuggyClass();
		assertEquals(-5, buggy.buggyMethod1(15, -3));
	}

}
