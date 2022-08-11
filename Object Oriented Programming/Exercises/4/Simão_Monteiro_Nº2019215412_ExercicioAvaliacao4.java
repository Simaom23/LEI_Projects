package exercicioavaliacao4;

/**
 * @author Simão Monteiro Nº2019215412
 */
public class ExercicioAvaliacao4 {

    public static void main(String[] args) {

        Livraria livraria = new Livraria();
        Livro l0 = new LivroTecnico("B. Kernighan", "\"The C Programming Language\"", 60, "Computer Science - C");
        livraria.addLivro(l0);
        Livro l1 = new LivroTecnico("H. Schildt", "\"Java: The Complete Reference\"", 80, "Computer Science - Java");
        livraria.addLivro(l1);
        Livro l2 = new LivroTecnico("E. Gamma et al.", "\"Design Patterns\"", 80, "Computer Science - Basics");
        livraria.addLivro(l2);
        Livro l3 = new LivroTecnico("M. Fowler", "\"UML Distilled\"", 70, "Computer Science - UML");
        livraria.addLivro(l3);
        Livro l4 = new LivroTecnico("D. Knuth", "\"The Art of Computer Programming\"", 90, "Computer Science - Basics");
        livraria.addLivro(l4);
        Livro l5 = new Aventuras("A. Christie", "\"The Man in the Brown Suit\"", 75, 14);
        livraria.addLivro(l5);
        Livro l6 = new Aventuras("J. K. Rowling", "\"Harry Potter and the Philosopher's Stone\"", 10, 12);
        livraria.addLivro(l6);
        Cliente c1 = new Premium("B. Antunes", "antunes@books.com");
        livraria.addCliente(c1);
        Cliente c2 = new Frequente("A. Oliveira", "oliveira@books.com");
        livraria.addCliente(c2);
        Cliente c3 = new Regular("C. Teodoro", "teodoro@books.com");
        livraria.addCliente(c3);
        Cliente c4 = new Premium("S. Monteiro", "monteiro@books.com");
        livraria.addCliente(c4);
        Cliente c5 = new Frequente("A. Sousa", "sousa@books.com");
        livraria.addCliente(c5);
        Cliente c6 = new Regular("V. Tomás", "tomas@books.com");
        livraria.addCliente(c6);
        livraria.showStock();
        System.out.println("\nCompras:");
        System.out.println(livraria.venda(l1, c3));
        System.out.println(livraria.venda(l2, c2));
        System.out.println(livraria.venda(l3, c1));
        System.out.println(livraria.venda(l5, c1));
        System.out.println(livraria.venda(l0, c4));
        System.out.println(livraria.venda(l4, c2));
        System.out.println(livraria.venda(l5, c1));
        System.out.println("\nVolume de vendas: " + livraria.getValorVendas() + "€\n");
        livraria.showStock();
        System.out.println();
        System.out.println(livraria.livrosCliente(c1));
        System.out.println(livraria.livrosCliente(c4));
    }
}
