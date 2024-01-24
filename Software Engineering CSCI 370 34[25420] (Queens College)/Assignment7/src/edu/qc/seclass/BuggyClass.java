package edu.qc.seclass;

public class BuggyClass {
	public Integer buggyMethod1(int X, int Y) {
		  Integer Z;
		  if (Y == 0){
			throw new IllegalArgumentException("Argument 'divisor' is 0");
		  } 
		  else if (Y > 0){
			Z = X/Y;
		  }
		  else {
			Z = X/Y;
		  }
		  
		  return Z;
	}
	
	
	public void buggyMethod2(int a, int b, boolean p) {
	    float result = 1;
        if (p == true){
            result = a / b;
        }
        else{
            b = b + 2;
            result = a / b;
        }
        System.out.println(result);
	}

	

	public void buggyMethod3(int a, int b) {
        float result = 1;
        if (b == 0) {
            b = b + 5;
            result = a / b;
        }
        else {
            b = b - b;
            result = a / b;

        }
	}
	
	public void buggyMethod4() {
        /* Having a test suite which has 100 % branch coverage and not revealing the fault AND
           every test suite which has 100 % statement coverage revealing the fault is not possible because
           branch coverage supersedes statement coverage meaning that it will identify more faults (if any) than
           statement coverage. */
	}
	
	
	public void buggyMethod5() {
		/* Its possible to ignore line 4 and skip that devide by zero however, you can never meet the first
		requirement then. You can't have 100% statement coverage */
	 }
}
