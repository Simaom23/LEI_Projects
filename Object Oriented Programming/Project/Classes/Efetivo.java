package projetopoo;

/**
 *
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
import java.io.*;

/**
 * Define os Investigadores do tipo Efetivo.
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
public class Efetivo extends Investigador implements Serializable{

    private int nGabinete;
    private int nTelefone;

    /**
     * Contrutor da classe Efetivo.
     * @param nGabinete Nº Gabinete do Efetivo.
     * @param nTelefone Nº Telefone do Efetivo.
     * @param nome Nome do Efetivo.
     * @param email Email do Efetivo.
     * @param grupo Grupo do Efetivo.
     */
    public Efetivo(int nGabinete, int nTelefone, String nome, String email, String grupo) {
        super(nome, email, grupo);
        this.nGabinete = nGabinete;
        this.nTelefone = nTelefone;
    }
    
    /**
     *
     * @return Tipo de Inestigador Efetivo (1).
     */
    @Override
    public int tipoInvest(){
        return 1;
    }

    /**
     *
     * @return String para imprimir informação do Efetivo.
     */
    @Override
    public String toString() {
        return "Efetivo -> Nome: " + getNome() + ", Email: " + getEmail() + ", Grupo: " + getGrupo() + ", Nº Gabinete: " 
                + nGabinete + ", Nº Telefone: " + nTelefone ;
    }

}
