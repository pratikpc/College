import java.util.Scanner;

public class MinOf3 {
	private static long minimum(final long n1, final long n2, final long n3) {
		// If n1<n2, check if its n1<n3
		// Else check if n2 < n3
		return (n1 < n2) ? ((n1 < n3) ? n1 : n3) : ((n2 < n3) ? n2 : n3);
	}
	private static long displayAndInput(Scanner read_input, final int pos) {
		System.out.print("Enter No " + pos + "\t:");
		return read_input.nextLong();		
	}
	public static void main(final String[] args) {
		Scanner read_input = new Scanner(System.in);
		final long n1 = displayAndInput(read_input, 1);
		final long n2 = displayAndInput(read_input, 2);
		final long n3 = displayAndInput(read_input, 3);

		final long min = minimum(n1,n2,n3);
		
		System.out.println("The minimum of 3 numbers is " + min);
	}
}