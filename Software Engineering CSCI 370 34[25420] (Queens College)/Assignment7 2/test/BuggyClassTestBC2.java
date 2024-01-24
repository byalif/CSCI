package edu.qc.seclass;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class BuggyClassTestBC2 {

	@Test
	void test() {
		  BuggyClass buggy = new BuggyClass();
		  buggy.buggyMethod2(10, 5, true);
		  buggy.buggyMethod2(5,1,false);
	      buggy.buggyMethod2(6, 5, true);
	      buggy.buggyMethod2(8,2,false);
	}
}
