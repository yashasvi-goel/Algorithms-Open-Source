import java.util.ArrayList;
import java.util.Scanner;

class Function{
	ArrayList<Double> coefficients = new ArrayList<Double>();
	ArrayList<Double> powers = new ArrayList<Double>();
	ArrayList<Double> differentialCoefficients = new ArrayList<Double>();
	ArrayList<Double> differentialPowers = new ArrayList<Double>();
	int terms = 0;
	final double maxDeviation = 0.00001;
	final int maxIterations = 500000;
	final int maxTries = 1000;
	static final double sentinel = Double.MIN_VALUE;
	static int tries = 0;
	
	double f(double x) {
		double result = 0;
		for(int i = 0; i < terms; ++i) {
			result += coefficients.get(i) * Math.pow(x, powers.get(i));
		}
		return result;
	}
	
	double fPrime(double x) {
		double result = 0;
		for(int i = 0; i < terms; ++i) {
			result += differentialCoefficients.get(i) * Math.pow(x, differentialPowers.get(i));
		}
		return result;
	}
	
	
	void findDifferential() {
		for(int i = 0; i < terms; ++i) {
			double value = coefficients.get(i) * powers.get(i);
			differentialCoefficients.add(value);
			if(powers.get(i) == 0) {
				differentialPowers.add(powers.get(i));
			}
			else {
				differentialPowers.add(powers.get(i) - 1);
			}
		}
	}
	
	double calculate() {
		terms = coefficients.size();
		findDifferential();
		return solve();
	}
	
	double solve() {
		double y = Double.MAX_VALUE;
		double x = Math.random();
		int iterations = 0;
		
		while(Math.abs(y) > maxDeviation && iterations < maxIterations) {
			try {
				double result = x - f(x)/fPrime(x);
				
				x = result;
				y = f(x);
			}
			catch(ArithmeticException e) {
				//due to fPrime(x) being 0
				x /= 2;
			}
			++iterations;
		}
		if(iterations == maxIterations) {
			//try again
			if(tries < maxTries) {
				++tries;
				return solve();
			}
			else {
				return Function.sentinel;
			}
		}
		return x;
	}
}


public class Solver {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		
		Function myFunction = new Function();
		
		System.out.print("Terms : ");
		int terms = Integer.parseInt(scanner.next());
		
		System.out.print("Coefficients : ");
		
		for(int i = 1; i <= terms; ++i) {
			try {
				double value = Double.parseDouble(scanner.next());
				
				myFunction.coefficients.add(value);
			}
			catch(NumberFormatException e) {
				System.out.println("Exception : " + e + " at element : " + i);
				System.out.println("Please enter a valid number and try again!");
				System.exit(-1);
			}
			catch(Exception e) {
				System.out.println("Exception : " + e);
				System.out.println("Please enter a valid input and try again!");
				System.exit(-1);
			}
		}
		
		System.out.print("Powers : ");
		
		for(int i = 1; i <= terms; ++i) {
			try {
				double value = Double.parseDouble(scanner.next());
				
				myFunction.powers.add(value);
			}
			catch(NumberFormatException e) {
				System.out.println("Exception : " + e + " at element : " + i);
				System.out.println("Please enter a valid number and try again!");
				System.exit(-1);
			}
			catch(Exception e) {
				System.out.println("Exception : " + e);
				System.out.println("Please enter a valid input and try again!");
				System.exit(-1);
			}
		}

		double result = myFunction.calculate();
		
		if(result == Function.sentinel) {
			System.out.println("Root does not exist!");
		}
		else {
			System.out.println("A root of the equation is : " + result);
		}
		
		scanner.close();
		
	}
}
