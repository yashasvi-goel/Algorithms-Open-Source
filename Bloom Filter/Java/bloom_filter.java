import com.google.common.hash.HashFunction;

import java.math.BigInteger;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.List;

import static com.google.common.hash.Hashing.murmur3_32;

//Implementation Based on "Building a Better Bloom Filter" https://www.eecs.harvard.edu/~michaelm/postscripts/tr-02-05.pdf
public class BloomFilter {

    //SHA 256 Algorithm on the URL
    public static byte[] sha256(String url) throws NoSuchAlgorithmException {
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        return digest.digest(url.getBytes(StandardCharsets.UTF_8));
    }

    //Murmur Hash Implementation 32 Bytes
    //Quick to calculate
    public static byte[] murmurHash(String url){
        HashFunction function = murmur3_32();
        String hash = function.hashBytes(url.getBytes()).toString();
        return hash.getBytes(StandardCharsets.UTF_8);
    }

    public static void main(String[] args) throws NoSuchAlgorithmException {
        //Here is a list of Unsafe URLs.
        List<String> unSafeURLs = new ArrayList<>();
        unSafeURLs.add("www.xyz.in");
        unSafeURLs.add("www.hacking.com");
        unSafeURLs.add("www.abc123.org");
        unSafeURLs.add("www.pentest.com");
        unSafeURLs.add("www.gugle.com");

        //Size of the Filter
        int primeSize = 1009;

        //Hash Functions Used
        int k = 5;

        //Initialising the Filter to be set to False
        boolean[] bloomFilter = new boolean[primeSize];

        for(String url: unSafeURLs){
            BigInteger hash1 = new BigInteger(sha256(url));
            BigInteger hash2 = new BigInteger(murmurHash(url));

            //g(x) = h1(x) + h2(x)*i mod P
            for(int i=0;i<k;i++){
                BigInteger b = hash1.add(hash2.multiply(BigInteger.valueOf(i)));
                b = b.mod(BigInteger.valueOf(primeSize));
                bloomFilter[b.intValue()] = true;
            }
        }

        //Sample set of URLs which contain both safe and unsafe URLs
        List<String> testSetURLs = new ArrayList<>();
        testSetURLs.add("www.google.com");
        testSetURLs.add("www.gugle.com");
        testSetURLs.add("www.github.com");
        testSetURLs.add("www.facebook.com");
        testSetURLs.add("www.xyz.in");

        for(String url : testSetURLs){
            BigInteger hash1 = new BigInteger(sha256(url));
            BigInteger hash2 = new BigInteger(murmurHash(url));

            //If for at least 2 distinct values of i the filter matches then we can say the URL belongs to the Unsafe URLs
            int counter = 0;
            for(int i=0;i<k;i++){
                BigInteger b = hash1.add(hash2.multiply(BigInteger.valueOf(i)));
                b = b.mod(BigInteger.valueOf(primeSize));
                if(bloomFilter[b.intValue()])
                    counter++;
            }
            if(counter>=2){
                System.out.println("The url: "+url+" is insecure");
            }
            else{
                System.out.println("The url: "+url+" is secure");
            }
        }
    }
}
