package exercicioavaliacao2;
/**
 * @author Simão Monteiro
 */
public class ExercicioAvaliacao2 {

    public static void main(String[] args) {
        int[][] tabela = {{40}, {2, 4, 6}, {7, 5}, {5, 7}, {}, {12, -15}, {1, 3, 7, 8}};
        System.out.printf("Exemplo de Tabela:\n");
        for (int[] tabela1 : tabela) {
            for (int j = 0; j < tabela1.length; j++) {
                System.out.printf("%1d\t", tabela1[j]);
            }
            System.out.println();
        }
        System.out.println();
        ordena(tabela);
    }

    public static int ordena(int[][] tab) {
        int[] soma = new int[tab.length];
        int cont = 0;
        for (int[] tab1 : tab) {
            for (int j = 0; j < tab1.length; j++) {
                int somar = tab1[j];
                soma[cont] += somar;
            }
            cont++;
        }
        for (int i = 0; i < soma.length - 1; i++) {
            for (int j = 0; j < soma.length - i - 1; j++) {
                if (soma[j] == soma[j + 1] & tab[j].length > tab[j + 1].length) {
                    int[] temp_array = new int[tab[j + 1].length];
                    System.arraycopy(tab[j + 1], 0, temp_array, 0, temp_array.length);
                    tab[j + 1] = new int[tab[j].length];
                    System.arraycopy(tab[j], 0, tab[j + 1], 0, tab[j + 1].length);
                    tab[j] = new int[temp_array.length];
                    System.arraycopy(temp_array, 0, tab[j], 0, tab[j].length);
                } else if (soma[j] > soma[j + 1]) {
                    int temp = soma[j];
                    soma[j] = soma[j + 1];
                    soma[j + 1] = temp;
                    int[] temp_array = new int[tab[j + 1].length];
                    System.arraycopy(tab[j + 1], 0, temp_array, 0, temp_array.length);
                    tab[j + 1] = new int[tab[j].length];
                    System.arraycopy(tab[j], 0, tab[j + 1], 0, tab[j + 1].length);
                    tab[j] = new int[temp_array.length];
                    System.arraycopy(temp_array, 0, tab[j], 0, tab[j].length);
                }
            }
        }
        System.out.printf("Tabela Ordenada:\n");
        for (int i = 0; i < tab.length; i++) {
            for (int j = 0; j < tab[i].length; j++) {
                System.out.printf("%1d\t", tab[i][j]);
            }
            System.out.printf("\\\\%d", soma[i]);
            System.out.println();
        }
        return 0;
    }
}
