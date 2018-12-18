import java.util.Scanner;

public class NaturalSum
{
	private static long getSum(final long n)
	{
		//As sum is from 1,2,3..n use Formula of AP
		return (n*(n+1))/2; // Uses formula n(n+1)/2
	}
	
	public static void main(final String[] args)
	{
		System.out.print("Enter number on which sum has to be calculated\t:");
		Scanner read = new Scanner(System.in);
		long n = read.nextLong();
		System.out.println("\nThe Sum was " + getSum(n));
	}
}