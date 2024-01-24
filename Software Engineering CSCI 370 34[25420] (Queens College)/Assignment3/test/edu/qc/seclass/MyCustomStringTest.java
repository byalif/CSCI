package edu.qc.seclass;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.fail;

public class MyCustomStringTest {

    private MyCustomStringInterface mycustomstring;

    @Before
    public void setUp() {
        mycustomstring = new MyCustomString();
    }

    @After
    public void tearDown() {
        mycustomstring = null;
    }

    //testCountNumbers
    
    @Test
    public void testCountNumbers1() {
        mycustomstring.setString("I'd b3tt3r put s0me d161ts in this 5tr1n6, right?");
        //passed
        assertEquals(7, mycustomstring.countNumbers());
    }

    @Test (expected = NullPointerException.class)
    public void testCountNumbers2() {
    	//Did not initialize a string so this will be null..
    	mycustomstring.countNumbers();
    }
    
    @Test
    public void testCountNumbers3() {
    	mycustomstring.setString("");
    	//Should equal to zero because empty string..
    	assertEquals(0, mycustomstring.countNumbers());
    }

    @Test
    public void testCountNumbers4() {
    	//Should equal to two because only 2 numbers in string..
    	mycustomstring.setString("This string has numbers 23 and 45");
    	assertEquals(2, mycustomstring.countNumbers());
    }
    
    @Test
    public void testCountNumbers5() {
    	//Should equal to 3 because only 3 consecutive numbers in string..
    	mycustomstring.setString("This string has numbers 5550 and 0+409");
    	assertEquals(3, mycustomstring.countNumbers());
    }

    @Test
    public void testCountNumbers6() {
    	//Should equal 0 because no numbers..
    	mycustomstring.setString("This string has no numbers");
    	assertEquals(0, mycustomstring.countNumbers());
    }
    
    @Test
    public void testCountNumbers7() {
    	//Did not initialize String..
    	assertNull(mycustomstring.getString());
    }
    
    @Test
    public void testCountNumbers8() {
    	//Should equal to two because only 2 numbers in string..
    	mycustomstring.setString("39823 and 45");
    	assertEquals(2, mycustomstring.countNumbers());
    }
    
    
    @Test
    public void testCountNumbers10() {
    	//Should equal to two because only 2 consecutive numbers in string..
    	mycustomstring.setString("459r0388498394893489");
    	assertEquals(2, mycustomstring.countNumbers());
    }



    //testGetEveryNthCharacterFromBeginningOrEnd

    @Test
    public void testGetEveryNthCharacterFromBeginningOrEnd1() {
        mycustomstring.setString("I'd b3tt3r put s0me d161ts in this 5tr1n6, right?");
        //passed
        assertEquals("d33p md1  i51,it", mycustomstring.getEveryNthCharacterFromBeginningOrEnd(3, false));
    }

    @Test
    public void testGetEveryNthCharacterFromBeginningOrEnd2() {
        mycustomstring.setString("I'd b3tt3r put s0me d161ts in this 5tr1n6, right?");
        //Same as previous test case but reversed..
        assertEquals("'bt t0 6snh r6rh", mycustomstring.getEveryNthCharacterFromBeginningOrEnd(3, true));
    }

    @Test (expected = NullPointerException.class)
    public void testGetEveryNthCharacterFromBeginningOrEnd3() {
    	//Did not initialize a string so this will be null..
    	mycustomstring.getEveryNthCharacterFromBeginningOrEnd(3, false);
    }

    @Test (expected = IllegalArgumentException.class)
    public void testGetEveryNthCharacterFromBeginningOrEnd4() {
    	//The parameter is less then zero which raises an illegal argument...
    	mycustomstring.getEveryNthCharacterFromBeginningOrEnd(-3, false);
    }

    @Test
    public void testGetEveryNthCharacterFromBeginningOrEnd5() {
    	mycustomstring.setString("This is a short string");
    	//Will return empty string because the parameter n is larger then string length
        assertEquals("", mycustomstring.getEveryNthCharacterFromBeginningOrEnd(53, false));
    }
    
    @Test (expected = NullPointerException.class)
    public void testGetEveryNthCharacterFromBeginningOrEnd6() {
    	mycustomstring.setString(null);
    	//String is null
    	mycustomstring.getEveryNthCharacterFromBeginningOrEnd(3, false);
    }
    
    @Test
    public void testGetEveryNthCharacterFromBeginningOrEnd7() {
    	mycustomstring.setString(" ");
    	//The parameter is out of bounds...
    	 assertEquals("", mycustomstring.getEveryNthCharacterFromBeginningOrEnd(35, true));
    }
    
    
    @Test
    public void testGetEveryNthCharacterFromBeginningOrEnd8() {
        mycustomstring.setString("Eating n00dles for lunch haha");
        //This is a valid test case and passes..
        assertEquals("aign0lsfrlnhhh", mycustomstring.getEveryNthCharacterFromBeginningOrEnd(2, true));
    }
    
    @Test
    public void testGetEveryNthCharacterFromBeginningOrEnd9() {
    	//null string shouldn't move forward
        assertNull(mycustomstring.getString());
    }
    

    
    //testConvertDigitsToNamesInSubstring

    @Test
    public void testConvertDigitsToNamesInSubstring1() {
        mycustomstring.setString("I'd b3tt3r put s0me d161ts in this 5tr1n6, right?");
        mycustomstring.convertDigitsToNamesInSubstring(17, 23);
        //passed
        assertEquals("I'd b3tt3r put sZerome dOneSix1ts in this 5tr1n6, right?", mycustomstring.getString());
    }

    @Test (expected = NullPointerException.class)
    public void testConvertDigitsToNamesInSubstring2() {
       //Did not initialize any string. This will raise a null pointer by default
        mycustomstring.convertDigitsToNamesInSubstring(17, 23);
    }

    @Test (expected = IllegalArgumentException.class)
    public void testConvertDigitsToNamesInSubstring3() {
    	//Start position is greater then end position so this will be illegal..
        mycustomstring.convertDigitsToNamesInSubstring(27, 23);
    }

    @Test (expected = MyIndexOutOfBoundsException.class)
    public void testConvertDigitsToNamesInSubstring4() {
    	mycustomstring.setString("hiii dude");
    	//start position is less then zero, thus index out of bounds
        mycustomstring.convertDigitsToNamesInSubstring(-3, 23);
    }

    @Test (expected = MyIndexOutOfBoundsException.class)
    public void testConvertDigitsToNamesInSubstring5() {
    	mycustomstring.setString("hiii dude");
    	//end position is greater then string length, thus index out of bounds
        mycustomstring.convertDigitsToNamesInSubstring(3, 800);
    }
    
    @Test (expected = IllegalArgumentException.class)
    public void testConvertDigitsToNamesInSubstring6() {
     	mycustomstring.setString("");
    	//Parameters are valid but not for an empty string..
        mycustomstring.convertDigitsToNamesInSubstring(27, 23);
    }

    @Test (expected = IllegalArgumentException.class)
    public void testConvertDigitsToNamesInSubstring7() {
     	mycustomstring.setString("fff");
    	//Parameters are valid but string length is shorter then end parameter
        mycustomstring.convertDigitsToNamesInSubstring(27, 23);
    }
    
    @Test
    public void testConvertDigitsToNamesInSubstring8() {
     	mycustomstring.setString("f5f");
        mycustomstring.convertDigitsToNamesInSubstring(1, mycustomstring.getString().length()-1);
    	//This should pass
        assertEquals("fFivef", mycustomstring.getString());
    }


    @Test
    public void testConvertDigitsToNamesInSubstring9() {
     	mycustomstring.setString("this string is c00l");
        mycustomstring.convertDigitsToNamesInSubstring(1, mycustomstring.getString().length()-1);
    	//This should pass
        assertEquals("this string is cZeroZerol", mycustomstring.getString());
    }
    
    @Test
    public void testConvertDigitsToNamesInSubstring10() {
     	mycustomstring.setString("12345");
        mycustomstring.convertDigitsToNamesInSubstring(1, mycustomstring.getString().length()-1);
    	//This should pass
        assertEquals("OneTwoThreeFour5", mycustomstring.getString());
    }


}
