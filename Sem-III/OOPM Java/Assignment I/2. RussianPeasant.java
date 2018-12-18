import java.util.Scanner;

public class RussianPeasant
{
	private static long getRussianPeasant(final long n1, final long n2)
	{
		long num = n1;
		long product = n2;
		
		// Multiply product by 2 till The First Number becomes 1
		// After First is Divided
		while(num != 1) // Continue Loop till 1 Reached
		{
			// This is how Russian Peasant Works
			num /= 2;
			product *= 2;
		}
		return product;
	}
	
	public static void main(final String[] args)
	{
		Scanner read = new Scanner(System.in);
		
		System.out.print("Enter First Number to Multiply\t:");
		long n1 = read.nextLong();
		System.out.print("Enter Second Number to Multiply\t:");
		long n2 = read.nextLong();
		System.out.println("\nThe Product was " + getRussianPeasant(n1,n2));
	}
}
