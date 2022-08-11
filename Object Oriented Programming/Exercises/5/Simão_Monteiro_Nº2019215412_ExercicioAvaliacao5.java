package exercicioavaliacao5;

/**
 *
 * @author Simão Monteiro
 */
import java.util.Scanner;
import java.io.*;
import java.util.ArrayList;

public class ExercicioAvaliacao5 {

    public static void main(String[] args) {
        Inscricao controlo = new Inscricao();
        File readAlunos = new File("Alunos.obj");
        File readDisciplinas = new File("Disciplinas.obj");
        if (readAlunos.exists() && readAlunos.isFile() && readDisciplinas.exists() && readDisciplinas.isFile()) {
            try {
                ObjectInputStream ois = new ObjectInputStream(new FileInputStream("Alunos.obj"));
                Aluno newAluno = null;
                try {
                    while (true) {
                        newAluno = (Aluno) ois.readObject();
                        controlo.addAluno(newAluno);
                    }
                } catch (EOFException ex) {
                    ois.close();
                }
            } catch (FileNotFoundException ex) {
                System.out.println("Erro a abrir ficheiro.");
            } catch (IOException ex) {
                System.out.println("Erro a ler ficheiro.");
            } catch (ClassNotFoundException ex) {
                System.out.println("Erro a converter objeto.");
            }
            
            try {
                ObjectInputStream ois = new ObjectInputStream(new FileInputStream("Disciplinas.obj"));
                Disciplina newDisciplina = null;
                try {
                    while (true) {
                        newDisciplina = (Disciplina) ois.readObject();
                        controlo.addDisciplina(newDisciplina);
                    }
                } catch (EOFException ex) {
                    ois.close();
                }
            } catch (FileNotFoundException ex) {
                System.out.println("Erro a abrir ficheiro.");
            } catch (IOException ex) {
                System.out.println("Erro a ler ficheiro.");
            } catch (ClassNotFoundException ex) {
                System.out.println("Erro a converter objeto.");
            }
        } else {
            File alunosText = new File("Alunos.txt");
            if (alunosText.exists() && alunosText.isFile()) {
                try {
                    BufferedReader br = new BufferedReader(new FileReader(alunosText));
                    String line;
                    while ((line = br.readLine()) != null) {
                        String[] elementos = line.split(",");
                        String nomeAluno = elementos[0];
                        int numAluno;
                        try {
                            numAluno = Integer.parseInt(elementos[1]);
                        } catch (NumberFormatException e) {
                            numAluno = -1;
                            System.out.printf("\nNúmero do Aluno com nome %s inserido incorretamente.\n", nomeAluno);
                        }
                        Aluno newAluno = new Aluno(nomeAluno, numAluno);
                        controlo.addAluno(newAluno);
                    }
                    br.close();
                } catch (FileNotFoundException e) {
                    System.out.println("\nErro a abrir ficheiro de texto.\n");
                } catch (IOException e) {
                    System.out.println("\nErro a ler ficheiro de texto.\n");
                }
            } else {
                System.out.println("\nFicheiro não existe.\n");
            }
            File readFile = new File("Disciplinas.txt");
            if (readFile.exists() && readFile.isFile()) {
                try {
                    BufferedReader br = new BufferedReader(new FileReader(readFile));
                    String line;
                    while ((line = br.readLine()) != null) {
                        String[] elementos = line.split(",");
                        String nomeDisciplina = elementos[0];
                        String sigla = elementos[1].toUpperCase();
                        int ects;
                        try {
                            ects = Integer.parseInt(elementos[2]);
                        } catch (NumberFormatException e) {
                            ects = -1;
                            System.out.printf("Número de ECTS mal inserido na disciplina com nome %s.", nomeDisciplina);
                        }
                        line = br.readLine();
                        elementos = line.split(",");
                        ArrayList<Aluno> inscritos = new ArrayList<>();
                        for (String add : elementos) {
                            int num = 0;
                            try {
                                num = Integer.parseInt(add);
                            } catch (NumberFormatException e) {
                                num = -1;
                                System.out.printf("Número de aluno mal inserido na disciplina com nome %s.", nomeDisciplina);
                            }
                            inscritos.add(controlo.searchAluno(num));
                        }
                        Disciplina newDisciplina = new Disciplina(nomeDisciplina, sigla, ects, inscritos);
                        controlo.addDisciplina(newDisciplina);  
                    }
                    br.close();
                } catch (FileNotFoundException e) {
                    System.out.println("\nErro a abrir ficheiro de texto.\n");
                } catch (IOException e) {
                    System.out.println("\nErro a ler ficheiro de texto.\n");
                }
            } else {
                System.out.println("\nFicheiro não existe.\n");
            }
        }

        Scanner input = new Scanner(System.in);
        int escolha = 0;
        boolean flag = false;
        while (!flag) {
            while (!flag) {
                System.out.printf("1 - Adicionar Aluno\n2 - Remover Aluno\n3 - Listar todas as Disciplinas\n0 - Sair\nEscolha -> ");
                if (input.hasNextInt()) {
                    escolha = input.nextInt();
                    if (escolha >= 0 && escolha <= 3) {
                        flag = true;
                    }
                } else {
                    System.out.println("Selecione o número da sua escolha.");
                }
                input.nextLine();
            }
            flag = false;
            switch (escolha) {
                case 1:
                    int num = 0;
                    while (!flag) {
                        System.out.printf("Introduza o número do aluno que deseja adicionar: ");
                        if (input.hasNextInt()) {
                            num = input.nextInt();
                            flag = true;
                        } else {
                            System.out.println("Introduza um número válido.");
                        }
                        input.nextLine();
                    }
                    System.out.printf("Introduza a sigla da disciplina a que deseja adicionar: ");
                    String cadeiraAdd = input.nextLine();
                    controlo.addInscricao(num, cadeiraAdd);
                    flag = false;
                    break;
                case 2:
                    num = 0;
                    while (!flag) {
                        System.out.printf("Introduza o número do aluno que deseja remover: ");
                        if (input.hasNextInt()) {
                            num = input.nextInt();
                            flag = true;
                        } else {
                            System.out.println("Introduza um número válido.");
                        }
                        input.nextLine();
                    }
                    System.out.printf("Introduza a sigla da disciplina a que deseja remover: ");
                    String cadeiraRem = input.nextLine();
                    controlo.delInscricao(num, cadeiraRem);
                    flag = false;
                    break;
                case 3:
                    controlo.listarDisciplinas();
                    break;
                case 0:
                    try {
                    ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("Alunos.obj"));
                    for (Aluno addObj : controlo.getListaAlunos()) {
                        oos.writeObject(addObj);
                    }
                    oos.close();
                } catch (FileNotFoundException ex) {
                    System.out.println("Erro a criar ficheiro de objetos.");
                } catch (IOException ex) {
                    System.out.println("Erro a escrever para o ficheiro de objetos.");
                }

                try {
                    ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("Disciplinas.obj"));
                    for (Disciplina addObj : controlo.getListaDisciplinas()) {
                        oos.writeObject(addObj);
                    }
                    oos.close();
                } catch (FileNotFoundException ex) {
                    System.out.println("Erro a criar ficheiro de objetos.");
                } catch (IOException ex) {
                    System.out.println("Erro a escrever para o ficheiro de objetos.");
                }

                try {
                    BufferedWriter bw = new BufferedWriter(new FileWriter("Alunos.txt"));
                    for (Aluno addObj : controlo.getListaAlunos()) {
                        bw.write(addObj.getNomeAluno() + "," + addObj.getNumAluno());
                        bw.newLine();
                    }
                    bw.close();
                } catch (IOException ex) {
                    System.out.println("Erro a escrever no ficheiro.");
                }

                try {
                    BufferedWriter bw = new BufferedWriter(new FileWriter("Disciplinas.txt"));
                    for (Disciplina addObj : controlo.getListaDisciplinas()) {
                        bw.write(addObj.getNomeDisciplina() + "," + addObj.getSigla() + "," + addObj.getEcts());
                        bw.newLine();
                        String all = "";
                        for (Aluno addInscritos : addObj.getInscritos()) {
                            all += addInscritos.getNumAluno() + ",";
                        }
                        String add = all.substring(0, all.length() - 1);
                        bw.write(add);
                        bw.newLine();
                    }
                    bw.close();
                } catch (IOException ex) {
                    System.out.println("Erro a escrever no ficheiro.");
                }
                flag = true;
                break;
            }
        }
    }
}
