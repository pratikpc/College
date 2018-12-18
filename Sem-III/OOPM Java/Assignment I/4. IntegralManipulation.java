import java.util.Scanner;

public class IntegralManipulation
{
	public static void main(final String [] args)
	{
		Scanner read_input = new Scanner(System.in);

		System.out.println("Enter the integral to manipulate");
		long n = read_input.nextLong();
		
		if(n < 0)//As n is supposed to be positive
			return;
		
		while(n != 1) // Repeat till n=1
			if(n%2 == 0)//Even
				n/=2; // If Even n/2
			else
				n = n*3 + 1; // If Odd do this

	}
}