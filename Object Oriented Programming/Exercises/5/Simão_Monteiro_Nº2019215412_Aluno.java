package exercicioavaliacao5;

/**
 *
 * @author Simão Monteiro
 */
import java.io.*;

public class Aluno implements Serializable {

    private String nomeAluno;
    private int numAluno;

    public Aluno(String nomeAluno, int numAluno) {
        this.nomeAluno = nomeAluno;
        this.numAluno = numAluno;
    }

    public String getNomeAluno() {
        return nomeAluno;
    }

    public int getNumAluno() {
        return numAluno;
    }
    
    @Override
    public String toString() {
        return numAluno + " " + nomeAluno + "\n";
    }  
}
