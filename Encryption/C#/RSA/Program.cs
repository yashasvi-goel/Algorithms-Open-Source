using System;
using System.Numerics;
using System.Collections.Generic;

namespace P4
{
    class Program
    {
        static BigInteger CustomMod(BigInteger a, BigInteger b)
        {
          //Finds the actual modulus (a mod b) and not just the remainder
          if (a % b < 0)
          {
            return (a % b) + b;
          }
          return a % b;
        }

        static BigInteger ExtendedEuclideanAlgorithm(BigInteger e, BigInteger N)
        {
            //Given e, N
            //Returns d s.t. (e*d) mod N = 1
            List<BigInteger> q = new List<BigInteger>();
            List<BigInteger> p = new List<BigInteger>();

            BigInteger divisorA = e;
            BigInteger dividend = N;
            bool isModulus0 = (dividend % divisorA == 0);

            while(!isModulus0)
            {
              BigInteger divisorB = BigInteger.Divide(dividend, divisorA);
              BigInteger modulus = dividend % divisorA;

              q.Add(divisorB);
              dividend = divisorA;
              divisorA = modulus;
              if (modulus == 0)
              {
                isModulus0 = true;
              }
            }

            for (int i = 0; i <= q.Count; i++)
            {
              if (i == 0)
              {
                p.Add(new BigInteger(0));
              }
              else if (i == 1)
              {
                p.Add(new BigInteger(1));
              }
              else
              {
                p.Add(CustomMod(p[i-2] - BigInteger.Multiply(p[i-1], q[i-2]), N));
              }
            }

            return p[p.Count - 1];
        }

        static void Main(string[] args)
        {
            switch(args[0])
            {
              case "encrypt":
                BigInteger plain = new BigInteger.Parse(args[1]);
                BigInteger p = BigInteger.Parse(args[2]);
                BigInteger q = BigInteger.Parse(args[3]);
                BigInteger e = BigInteger.Parse(args[4]);
                BigInteger N = BigInteger.Multiply(p, q);

                Console.WriteLine(BigInteger.ModPow(plain, e, N));
                break;
              case "decrypt":
                BigInteger cipher = new BigInteger.Parse(args[1]);
                BigInteger p = BigInteger.Parse(args[2]);
                BigInteger q = BigInteger.Parse(args[3]);
                BigInteger d = BigInteger.Parse(args[4]);
                BigInteger phi_N = BigInteger.Multiply(p - 1, q - 1);

                Console.WriteLine(BigInteger.ModPow(plain, d, phi_N));
                break;
              case "findKeyPair":
                BigInteger p = BigInteger.Parse(args[1]);
                BigInteger q = BigInteger.Parse(args[2]);
                BigInteger key = BigInteger(args[3]);
                BigInteger N = BigInteger.Multiply(p, q);

                Console.WriteLine(ExtendedEuclideanAlgorithm(key, N))
                break;
              default:
                Console.WriteLine('Only valid commands:');
                Console.WriteLine('dotnet run encrypt {plaintext in base 10} {prime 1} {prime 2} {key}');
                Console.WriteLine('dotnet run decrypt {cipher in base 10} {prime 1} {prime 2} {key}');
                Console.WriteLine('dotnet run findKeyPair  {prime 1} {prime 2} {key}');
                break;
            }
        }
    }
}
