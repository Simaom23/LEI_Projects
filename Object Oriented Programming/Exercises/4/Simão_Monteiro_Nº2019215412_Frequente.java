package exercicioavaliacao4;

/**
 * @author Simão Monteiro Nº2019215412
 */
public class Frequente extends Cliente {

    public Frequente(String nome, String email) {
        super(nome, email);
    }

    @Override
    public double getDesconto() {
        return 0.95;
    }
}
