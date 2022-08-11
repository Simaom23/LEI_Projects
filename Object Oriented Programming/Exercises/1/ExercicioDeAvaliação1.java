package exercicio.de.avaliação.pkg1;
/*
 * @author Simão Monteiro
 */
import java.util.*;
public class ExercicioDeAvaliação1 {
    public static void main(String[] args) {
        int N = -1;
        while(N < 1 | N > 12){
            System.out.printf ("Introduza um número de 1 a 12: ");
            Scanner sc = new Scanner(System.in);
            N = sc.nextInt();
        }
        System.out.printf ("Número de linhas: %d\n", N);
        triangulo(N);
    }
    public static int fatorial (int n){
        int fat = 1;
        for(int i = 1; i <= n; i++){
            fat = fat * i;
        }
        return fat;
    }
    public static int triangulo (int linhas){
        for(int n = 0; n < linhas; n++){
            for(int space = linhas; space > n; space--){
                System.out.printf (" ");
            }
            for(int k = 0; k <= n; k++){
                int comb = (fatorial(n)/(fatorial(k) * fatorial(n-k)));
                int leter_n = comb;
                if(leter_n >= 26){
                    leter_n = leter_n % 26;
                    leter_n = leter_n + 65;
                }
                else{
                    leter_n = leter_n % 26;
                    leter_n = leter_n + 64;
                }
                char leter = (char) leter_n;
                System.out.printf ("%c ",leter);
            }
            System.out.println();
        }
        return 0;
    }
}
