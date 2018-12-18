import java.util.Scanner;

public class IntegerToString
{
	public static String toString0To9(final int i){
		switch(i){
			case 0:	return "zero ";
			case 1:	return "one ";
			case 2:	return "two ";
			case 3:	return "three ";
			case 4:	return "four ";
			case 5:	return "five ";
			case 6:	return "six ";
			case 7:	return "seven ";
			case 8:	return "eight ";
			case 9:	return "nine ";
			default:return "";
		}
	}
	private static int reverse(int n) {
		int rev = 0;
		while(n != 0) {
			rev *= 10;
			final int digit = n%10;
			rev += digit;
			n /= 10;
		}
		return rev;
	}
	public static String toString(int n) {
		String convert = "";
		n = reverse(n);
		while(n != 0) {
			final int digit = n%10;
			convert += toString0To9(digit);
			n /= 10;
		}	
		return convert;	
	}

	public static void main(final String[] args){
		Scanner read_input = new Scanner(System.in);

		System.out.println("Enter the integral to manipulate");
		final int n = read_input.nextInt();

		System.out.println("\nThe Number converted to String is " + toString(n));
	}
}