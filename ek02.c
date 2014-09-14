/*
    etherKeys
    (c) 2014-09-11 Peter Alaric DeSimone
    http://www.PeterAlaric.com
    for Lyratron, LLC
    http://www.lyratron.com

    DESCRIPTION: etherKeys is an innovative program that creates a virtual
    vault filled with secure, high-entropy encryption keys and passwords.
    Rather than save the vault to a computer's hard drive where it could
    potentially be discovered by others, the vault is only accessible through
    this program and is deleted after each use.  However, since the creation of
    the vault is algorithmic and is entirely dependent on initial conditions,
    these conditions can be recreated at any time by the rightful owner to again
    access the vault.  When not being accessed, the vault literally does not
    exist.  It has no physical location; no file system path, URL or other means
    by which it can be located.  There is also no evidence whatsoever that a
    person has created a vault or has used it to generate passwords or
    cryptographic keys they are actively using.  This means a court would not
    have probable cause to issue a subpoena for a person to surrender their
    vault, and if such a subpoena were issued, a person would have plausible
    deniability as to the very existence of the vault in question.

    A flow diagram of the program's typical use follows:

    1) etherKeys is launched by a user desiring secure keys for access control,
    online passwords or secret key cryptosystems.

    2) The user inputs a secret passphrase, and optionally demographic information
    for additional security, into EK.  This information in its totality will serve
    as the key to the vault.

    3) The vault is generated and displayed.

    4) The user selects keys from the list and uses them as passwords for online
    accounts, or as cryptographic keys to encrypt data.  The index number of each
    key used is kept in a text file along with a note that it was used for a
    particular purpose.  This text file does not need to be kept particularly
    secure because it contains vastly insufficient information for an attacker to
    successfully breach an account, and no information about how to access the
    user's vault.

    5) Whenever a key needs to be accessed, EK can be launched, the passphrase
    entered and the vault accessed.
 
    How does etherKeys work?

    1) The user's passphrase is inputted and stored in volatile RAM.
 
    2) Optionally, demographic info (date of birth, Social Security number, etc.)
    is entered and stored in volatile RAM.
 
    3) A secure hash of the data from Steps 1 and 2 is generated, using a trusted,
    NIST-approved algorithm such as SHA-2 or SHA-3.

    4) The hash from Step 3 is used as the secret key to prime a stream cipher or
    block cipher configured for OFB mode (output feedback).
 
    5) The stream cipher generates an infinite stream of random data, which is
    divided into blocks and mapped to the desired subset of the ASCII character
    set.

    6) A finite number of these ready-to-use keys are displayed to the screen at
    one time.  Optionally, the user may access additional screens through "next
    page" and "previous page" commands.
 
    7) Optionally, annotations may be added to each used key to remind the user
    what the key was used for.  These annotations are saved locally in an
    encrypted text file and loaded next time EK is run.
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define LEN             1000


/* a nonsecure method of computing a hash (for demo purposes). */
unsigned int compute_hash(char *s)
{
    unsigned int hash = 0;
    
    srand(1);
    unsigned long int i = 0;
    for (i = 0; i < strlen(s)-1; i++)
    {
        printf("%u \n", hash);
        hash = hash ^ rand() % 65535;
        hash = hash ^ (s[i] * (i+1));
        //hash += (s[i] ^ rand() % 256) % 65536;
    }
    
    return hash;
}


void print_random_key()
{
    unsigned int i = 0;
    for (i = 0; i < 10; i++)
    {
        char c = 0;
        int r = rand() %100;
        if (r < 33) c = 'a' + rand() %26;
        else if (r < 66) c = 'A' + rand() %26;
        else c = '0' + rand() % 10;
        printf("%c", c);
    }
}


void generate_keys(unsigned int hash, unsigned int num_keys)
{
    srand(hash);
    
    int columns = 5;
    
    unsigned int i = 0;
    for (i = 0; i < num_keys; i+=columns)
    {
        int j = 0;
        for (j = 0; j < columns; j++)
        {
            printf("%u: ", i+j);
            print_random_key();
            if (j < columns-1) printf("\t");
        }

        printf("\n");
    }
}



int main(int argc, char *argv[])
{
    printf("\n");
    printf("************* etherKeys ************\n");
    printf("*  (c) 2014 Peter Alaric DeSimone  *\n");
    printf("* Lyratron, LLC ~ www.lyratron.com *\n");
    printf("************************************\n");
    printf("\n");
    
    printf("\n");
    printf("WARNING: This is a cryptographically insecure version of EK,\n");
    printf("intended for demo purposes only.  Do not use to secure sensitive data!\n");
    printf("\n");
    
    // input passphrase string
    printf("passphrase: ");
    char s[LEN];
    //gets(s);
    fgets(s, LEN, stdin);
    
    // this might be a good time to detect and strip out any newline characters
    //printf("\n"); // <-- after newline removal, un-rem this line
    
    // confirm proper input (diagnostic)
    printf("you entered: %s", s);
    printf("\n");
    
    // take hash of passphrase string
    printf("computing hash...\n");
    unsigned int hash = compute_hash(s);

    printf("hash: %u \n\n", hash);
    
    generate_keys(hash, 100);
    
    printf("\n");
    
    return 0;
}
