#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

bool isPrime(int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

pair<int, int> generateKeys()
{
    srand(time(NULL));

    int p, q, n, phi, e, d;

    do
    {
        p = rand() % 100 + 1;
    } while (!isPrime(p));

    do
    {
        q = rand() % 100 + 1;
    } while (!isPrime(q) || q == p);

    n = p * q;
    phi = (p - 1) * (q - 1);

    do
    {
        e = rand() % phi;
    } while (gcd(e, phi) != 1);

    for (d = 2; d < phi; d++)
    {
        if ((d * e) % phi == 1)
        {
            break;
        }
    }

    return {e, d};
}

int encrypt(int message, int e, int n)
{
    return static_cast<int>(pow(message, e)) % n;
}

int decrypt(int encryptedMessage, int d, int n)
{
    return static_cast<int>(pow(encryptedMessage, d)) % n;
}

int main()
{
    auto keys = generateKeys();
    int e = keys.first;
    int d = keys.second;
    int n = 37 * 41;

    int originalMessage;
    cout << "Enter the message (integer) to encrypt: ";
    cin >> originalMessage;

    int encryptedMessage = encrypt(originalMessage, e, n);
    cout << "Encrypted message: " << encryptedMessage << endl;

    int decryptedMessage = decrypt(encryptedMessage, d, n);
    cout << "Decrypted message: " << decryptedMessage << endl;

    return 0;
}
