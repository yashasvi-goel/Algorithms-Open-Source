using System;
using System.Numerics;

namespace DiffieHellman
{
    class Program
    {
        static void Main(string[] args)
        {
          switch(args[0])
          {
            case 'generateKey':
              BigInteger keyHalf = BigInteger.Parse(args[1]);
              BigInteger N = BigInteger.Parse(args[2]);
              BigInteger x = BigInteger.Parse(args[3]);
              Console.WriteLine(BigInteger.ModPow(keyHalf, x, N));
              break;
            case 'generateKeyHalf':
              BigInteger g = BigInteger.Parse(args[1]);
              BigInteger N = BigInteger.Parse(args[2]);
              BigInteger x = BigInteger.Parse(args[3]);
              Console.WriteLine(BigInteger.ModPow(g, x, N));
              break;
            default:
              Console.WriteLine('Only valid commands:');
              Console.WriteLine('dotnet run generateKeyHalf {generator} {modulus} {exponent}');
              Console.WriteLine('dotnet run generateKey {KeyHalf} {moduls} {exponent}');
              break;
          }
        }
    }
}
