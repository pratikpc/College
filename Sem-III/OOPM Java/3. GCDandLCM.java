import java.util.Scanner;

public class GCDandLCM
{
	private static long gcd(final long m, final long n)
	{
		// If the remainder of 2 Numbers is Zero, it means GCD Has been found
		if(n == 0)
			// The GCD Value
			return m;
		if(m < n)
			// If m < n, then we know m%n == 0; But that is not we want
			// So we reverse the order
			return gcd(n,m);
		else
			return gcd(n,m%n);
	}
	private static long lcm(final long m, final long n)
	{
		// We Know by Formula, GCD * LCM = m * n
		// Then LCM = m * n /  GCD
		return (m * n)/ gcd(m,n);
	}
	public static void main(final String[] args)
	{
		Scanner read_input = new Scanner(System.in);
		
		System.out.print("\nEnter the first Number\t:");
		final long n1 = read_input.nextLong();
		System.out.print("\nEnter the Second Number\t:");
		final long n2 = read_input.nextLong();
		System.out.println("\nThe GCD is " + gcd(n1,n2) + " and the LCM is " + lcm(n1,n2));
	}
}