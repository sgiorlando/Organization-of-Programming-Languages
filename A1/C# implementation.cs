//Scott Giorlando
//Zachary did this language.

/*
Code Help from Rosetta Code
URL: http://rosettacode.org/wiki/Combinations#C#
*/

using System;
using System.Collections.Generic;

public class Program
{
  //It looks like FindCombosRec is a function that makes every possible combination of the numbers given from 1 to n.
  //It also appears to be a recursive function, which works better for compilation and run time.
  public static IEnumerable<int[]> FindCombosRec(int[] buffer, int done, int begin, int end)
  {
    for (int i = begin; i < end; i++)
    {
      buffer[done] = i;

      if (done == buffer.Length - 1)
        yield return buffer;
      else
        foreach (int[] child in FindCombosRec(buffer, done+1, i+1, end))
          yield return child;
    }
  }

  public static IEnumerable<int[]> FindCombinations(int m, int n)
  {
    return FindCombosRec(new int[m], 0, 0, n);
  }

  static void Main()
  {
    int k,n;
    Console.WriteLine("Please Enter the desired number of numbers:");
    k = Convert.ToInt32(Console.ReadLine());
    Console.WriteLine("Please Enter the desired n for the top of the range:");
    n = Convert.ToInt32(Console.ReadLine());
    //These foreach loops seem to use IEnumerable types.  I've never done C# so I'm kind of assuming that.
    //It does seem really interesting and very useful if used in the right situations.
    foreach (int[] c in FindCombinations(k, n))
    {
      for (int i = 0; i < c.Length; i++)
      {
        Console.Write(c[i] + " ");
      }
      Console.WriteLine();
    }
  }
}
