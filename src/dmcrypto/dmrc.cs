
// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

using System;
using System.Collections;

public class CDMRC
{
    public CDMRC()
    {
        byte[] key = new byte[256];
        for (int i = 0; i < 256; i++)
        {
            key[i] = 0;
        }

        SetEncryptKey(key, 256);
        SetDecryptKey(key, 256);
    }

    class arc4_context
    {
        public int x;                      /*!< permutation index */
        public int y;                      /*!< permutation index */
        public byte[] m = new byte[256];       /*!< permutation table */
    }

    arc4_context m_oEncryptContext = new arc4_context();
    arc4_context m_oDecryptContext = new arc4_context();

    public void SetKey(byte[] key, uint keylen)
    {
        SetEncryptKey(key, keylen);
        SetDecryptKey(key, keylen);
    }

    public void SetEncryptKey(byte[] key, uint keylen)
    {
        int i, j, a;
        uint k;
        byte[] m;

        m_oEncryptContext.x = 0;
        m_oEncryptContext.y = 0;
        m = m_oEncryptContext.m;

        for( i = 0; i < 256; i++ )
          m[i] = (byte) i;

        j = 0;
        k = 0;

        for( i = 0; i < 256; i++, k++ )
        {
            if( k >= keylen ) k = 0;

            a = m[i];
            j = ( j + a + key[k] ) & 0xFF;
            m[i] = m[j];
            m[j] = (byte) a;
        }
    }

    public void SetDecryptKey(byte[] key, uint keylen)
    {
        int i, j, a;
        uint k;
        byte[] m;

        m_oDecryptContext.x = 0;
        m_oDecryptContext.y = 0;
        m = m_oDecryptContext.m;

        for (i = 0; i < 256; i++)
          m[i] = (byte)i;

        j = 0;
        k = 0;

        for (i = 0; i < 256; i++, k++)
        {
            if (k >= keylen) k = 0;

            a = m[i];
            j = (j + a + key[k]) & 0xFF;
            m[i] = m[j];
            m[j] = (byte)a;
        }
    }

    static int arc4_crypt(arc4_context ctx, byte[] input, int iOffset, byte[] output, int oOffset, int length)
    {
        int x, y, a, b;
        int i;
        byte[] m;

        x = ctx.x;
        y = ctx.y;
        m = ctx.m;

        for( i = 0; i < length; i++ )
        {
            x = ( x + 1 ) & 0xFF; a = m[x];
            y = ( y + a ) & 0xFF; b = m[y];

            m[x] = (byte) b;
            m[y] = (byte) a;

            output[i + oOffset] = (byte)(input[i + iOffset] ^ m[(byte)(a + b)]);
        }

        ctx.x = x;
        ctx.y = y;

        return( 0 );
    }

    public int Encrypt(byte[] input, int iOffset, byte[] output, int oOffset, int length)
    {
        return arc4_crypt(m_oEncryptContext, input, iOffset, output, oOffset, length);
    }

    public int Decrypt(byte[] input, int iOffset, byte[] output, int oOffset, int length)
    {
        return arc4_crypt(m_oDecryptContext, input, iOffset, output, oOffset, length);
    }

    public int Encrypt(byte[] input)
    {
        return arc4_crypt(m_oEncryptContext, input, 0, input, 0, input.Length);
    }

    public int Decrypt(byte[] input)
    {
        return arc4_crypt(m_oDecryptContext, input, 0, input, 0, input.Length);
    }

    public string Encrypt(string input)
    {
        byte[] InArray = System.Text.Encoding.Default.GetBytes(input);

        arc4_crypt(m_oEncryptContext, InArray, 0, InArray, 0, InArray.Length);

        return System.Text.Encoding.Default.GetString(InArray);
    }

    public string Decrypt(string input)
    {
        byte[] InArray = System.Text.Encoding.Default.GetBytes(input);

        arc4_crypt(m_oDecryptContext, InArray, 0, InArray, 0, InArray.Length);

        return System.Text.Encoding.Default.GetString(InArray);
    }

    static void test(string[] args)
    {
        CDMRC oArc4 = new CDMRC();

        string strInput = "data";

        byte[] InArray = System.Text.Encoding.Default.GetBytes(strInput);
        byte[] OutArray = System.Text.Encoding.Default.GetBytes(strInput);

        oArc4.Encrypt(InArray, 0, OutArray, 0, InArray.Length);
        oArc4.Decrypt(OutArray, 0, InArray, 0, OutArray.Length);

        string strOut = System.Text.Encoding.Default.GetString(InArray);
        Console.WriteLine(strOut);

        string strOut2 = oArc4.Encrypt(strOut);
        string strOut3 = oArc4.Decrypt(strOut2);
        Console.WriteLine(strOut3);

        oArc4.Encrypt(InArray);
        oArc4.Decrypt(InArray);

        string strOut4 = System.Text.Encoding.Default.GetString(InArray);

        Console.WriteLine(strOut4);
    }
}

