package exercicioavaliacao4;

/**
 * @author Simão Monteiro Nº2019215412
 */
public class LivroTecnico extends Livro {

    private String area;

    public LivroTecnico() {
    }

    public LivroTecnico(String autor, String titulo, int preco, String area) {
        super(autor, titulo, preco);
        this.area = area;
    }

    public String getArea() {
        return area;
    }

    @Override
    public String toString() {
        return getTitulo() + ", Livro técnico de " + area;
    }

}
