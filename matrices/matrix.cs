using System;
using System.Text;
using System.Collections.Generic;
using System.Numerics;
using System.Linq;
using System.Text.RegularExpressions;

namespace zottt
{
    class Program
    {
        static void Main( string[] args )
        {
            int n         = int.Parse( Console.ReadLine() );
            int[,] matrix = new int[n, n];
            matrixx( n,  matrix );
            show_matrix( matrix, n );
        }

        static void matrixx( int n, int[,] matrix )
        {
            for ( int i = 0 ; i < n ; i++ ) {
                for ( int j = 0 ; j < n ; j++ ) {
                    matrix[i, j] = n;
                }
            }
        }

        static void show_matrix( int[,] matrix, int n )
        {
            for ( int i = 0 ; i < n ; i++ ) {
                for ( int j = 0 ; j < n ; j++ ) {
                    Console.Write( $"{matrix[i, j]} " );
                }
                Console.WriteLine();
            }
        }
    }
}