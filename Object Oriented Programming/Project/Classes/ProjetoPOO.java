package projetopoo;

/**
 *
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
import java.util.Scanner;
import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.text.SimpleDateFormat;
import java.text.DateFormat;
import java.text.ParseException;

/**
 * Classe que contem a função main e onde são abertos e lidos os diferentes
 * ficheiros e também contem o menu.
 *
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
public class ProjetoPOO {

    /**
     * Esta a função main em que sao abertos e lidos os diferentes ficheiros de
     * texto e objetos e também onde contém o Menu e sao chamadas todas as outras
     * funções do projeto.
     *
     * @param args
     *
     */
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        Cisuc cisuc = new Cisuc();
        System.out.println("# - Gestor de Publicações do CISUC - #");
        File grupos = new File("Grupos.obj");
        boolean flag = false;
        DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
        dateFormat.setLenient(false);
        int escolha = -1;
        while (!flag) {
            System.out.printf("Deseja carregar novos dados?(1-Sim | 0-Não) ");
            if (input.hasNextInt()) {
                escolha = input.nextInt();
                if (escolha == 0 || escolha == 1) {
                    flag = true;
                }
            } else {
                System.out.println("Selecione o número da sua escolha.");
            }
            input.nextLine();
        }
        if (!(grupos.exists() && grupos.isFile())) {
            if (escolha == 0) {
                System.out.println("É necessário adicionar dados visto que a base de dados se encontra vazia.");
                escolha = 1;
            }
        }
        if (escolha == 1) {
            File readFile = new File("Grupos.txt");
            if (readFile.exists() && readFile.isFile()) {
                try {
                    BufferedReader br = new BufferedReader(new FileReader(readFile));
                    String line;
                    br.readLine();
                    while ((line = br.readLine()) != null) {
                        String[] elementos = line.split(",");
                        String nome = elementos[0];
                        String acronimo = elementos[1];
                        String iResponsavel = elementos[2];
                        Grupo newGrupo = new Grupo(nome, acronimo, iResponsavel);
                        cisuc.addGrupo(newGrupo);
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
            readFile = new File("Efetivos.txt");
            if (readFile.exists() && readFile.isFile()) {
                try {
                    BufferedReader br = new BufferedReader(new FileReader(readFile));
                    String line;
                    line = br.readLine();
                    while ((line = br.readLine()) != null) {
                        String[] elementos = line.split(",");
                        String nome = elementos[0];
                        String email = elementos[1];
                        String grupo = elementos[2].toUpperCase();
                        int nGabinete;
                        try {
                            nGabinete = Integer.parseInt(elementos[3]);
                        } catch (NumberFormatException e) {
                            System.out.printf(
                                    "Número de Gabinete do Membro Efetivo %s pertencente ao grupo %s mal inserido no ficheiro de texto.\n",
                                    nome, grupo);
                            continue;
                        }
                        int nTelefone;
                        try {
                            nTelefone = Integer.parseInt(elementos[4]);
                        } catch (NumberFormatException e) {
                            System.out.printf(
                                    "Número de Telefone do Membro Efetivo %s pertencente ao grupo %s mal inserido no ficheiro de texto.\n",
                                    nome, grupo);
                            continue;
                        }
                        Efetivo newEfetivo = new Efetivo(nGabinete, nTelefone, nome, email, grupo);
                        cisuc.addMembro(newEfetivo, true);
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
            for (Grupo searchGrupo : cisuc.getGruposCisuc()) {
                int contemOrientador = 0;
                for (Investigador contemOri : searchGrupo.getMembros()) {
                    if (contemOri.getNome().toLowerCase().equals(searchGrupo.getiResponsavel().toLowerCase())) {
                        contemOrientador = 1;
                        break;
                    }
                }
                if (contemOrientador == 0) {
                    System.out.printf("Erro. O Investigador Responsável do Grupo %s não é nenhum efetivo.\n",
                            searchGrupo.getAcronimo());
                }
            }
            readFile = new File("Estudantes.txt");
            if (readFile.exists() && readFile.isFile()) {
                try {
                    BufferedReader br = new BufferedReader(new FileReader(readFile));
                    String line;
                    line = br.readLine();
                    while ((line = br.readLine()) != null) {
                        String[] elementos = line.split(",");
                        String nome = elementos[0];
                        String email = elementos[1];
                        String grupo = elementos[2].toUpperCase();
                        String cTese = elementos[3];
                        String cDate = elementos[4];
                        String orientador = elementos[5];
                        Estudante newEstudante = new Estudante(cTese, cDate, orientador, nome, email, grupo);
                        cisuc.addMembro(newEstudante, true);
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

            readFile = new File("ArtConferencia.txt");
            if (readFile.exists() && readFile.isFile()) {
                try {
                    BufferedReader br = new BufferedReader(new FileReader(readFile));
                    String line;
                    line = br.readLine();
                    while ((line = br.readLine()) != null) {
                        String[] elementos = line.split(",");
                        String[] autores = elementos[0].split("#");
                        String titulo = elementos[1];
                        String[] keywords = elementos[2].split("#");
                        int anoPub;
                        int dimensao;
                        try {
                            anoPub = Integer.parseInt(elementos[3]);
                        } catch (NumberFormatException e) {
                            System.out.printf("Erro no ano da conferência com título \"%s\".\n", titulo);
                            continue;
                        }
                        try {
                            dimensao = Integer.parseInt(elementos[4]);
                        } catch (NumberFormatException e) {
                            System.out.printf("Erro na dimensão da conferência com título \"%s\".\n", titulo);
                            continue;
                        }
                        String resumo = elementos[5];
                        String nomeConf = elementos[6];
                        String data = elementos[7];
                        String localizacao = elementos[8];
                        ArtConferencia newConf = new ArtConferencia(nomeConf, data, localizacao, autores, titulo,
                                keywords, anoPub, dimensao, resumo);
                        cisuc.addPub(newConf, true);
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

            readFile = new File("ArtRevista.txt");
            if (readFile.exists() && readFile.isFile()) {
                try {
                    BufferedReader br = new BufferedReader(new FileReader(readFile));
                    String line;
                    line = br.readLine();
                    while ((line = br.readLine()) != null) {
                        String[] elementos = line.split(",");
                        String[] autores = elementos[0].split("#");
                        String titulo = elementos[1];
                        String[] keywords = elementos[2].split("#");
                        int anoPub;
                        int dimensao;
                        try {
                            anoPub = Integer.parseInt(elementos[3]);
                        } catch (NumberFormatException e) {
                            System.out.printf("Erro no ano da revista com título \"%s\"\n.", titulo);
                            continue;
                        }
                        try {
                            dimensao = Integer.parseInt(elementos[4]);
                        } catch (NumberFormatException e) {
                            System.out.printf("Erro na dimensão da revista com título \"%s\"\n.", titulo);
                            continue;
                        }
                        String resumo = elementos[5];
                        String nome = elementos[6];
                        String data = elementos[7];
                        String numero = elementos[8];
                        ArtRevista newRev = new ArtRevista(nome, data, numero, autores, titulo, keywords, anoPub,
                                dimensao, resumo);
                        cisuc.addPub(newRev, true);
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

            readFile = new File("Livros.txt");
            if (readFile.exists() && readFile.isFile()) {
                try {
                    BufferedReader br = new BufferedReader(new FileReader(readFile));
                    String line;
                    line = br.readLine();
                    while ((line = br.readLine()) != null && line != "\n") {
                        String[] elementos = line.split(",");
                        String[] autores = elementos[0].split("#");
                        String titulo = elementos[1];
                        String[] keywords = elementos[2].split("#");
                        int anoPub;
                        int dimensao;
                        try {
                            anoPub = Integer.parseInt(elementos[3]);
                        } catch (NumberFormatException e) {
                            System.out.printf("Erro no ano do livro com título \"%s\"\n.", titulo);
                            continue;
                        }
                        try {
                            dimensao = Integer.parseInt(elementos[4]);
                        } catch (NumberFormatException e) {
                            System.out.printf("Erro na dimensão do livro com título \"%s\"\n.", titulo);
                            continue;
                        }
                        String resumo = elementos[5];
                        String autora = elementos[6];
                        String isbn = elementos[7];
                        Livro newLivro = new Livro(autora, isbn, autores, titulo, keywords, anoPub, dimensao, resumo);
                        cisuc.addPub(newLivro, true);
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

            readFile = new File("LivrosConf.txt");
            if (readFile.exists() && readFile.isFile()) {
                try {
                    BufferedReader br = new BufferedReader(new FileReader(readFile));
                    String line;
                    line = br.readLine();
                    while ((line = br.readLine()) != null) {
                        String[] elementos = line.split(",");
                        String[] autores = elementos[0].split("#");
                        String titulo = elementos[1];
                        String[] keywords = elementos[2].split("#");
                        int anoPub;
                        int dimensao;
                        try {
                            anoPub = Integer.parseInt(elementos[3]);
                        } catch (NumberFormatException e) {
                            System.out.printf("Erro no ano do livro de artigos de confência com título \"%s\"\n.",
                                    titulo);
                            continue;
                        }
                        try {
                            dimensao = Integer.parseInt(elementos[4]);
                        } catch (NumberFormatException e) {
                            System.out.printf("Erro na dimensão do livro de artigos de confência com título \"%s\"\n.",
                                    titulo);
                            continue;
                        }
                        String resumo = elementos[5];
                        String autora = elementos[6];
                        String isbn = elementos[7];
                        String nomeConf = elementos[8];
                        int nArtigos;
                        try {
                            nArtigos = Integer.parseInt(elementos[9]);
                        } catch (NumberFormatException e) {
                            System.out.printf(
                                    "Erro no número de artigos do livro de artigos de conferência com título \"%s\"\n.",
                                    titulo);
                            continue;
                        }
                        LivroConferencia newLivroConf = new LivroConferencia(nomeConf, nArtigos, autora, isbn, autores,
                                titulo, keywords, anoPub, dimensao, resumo);
                        cisuc.addPub(newLivroConf, true);
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

            readFile = new File("CapLivros.txt");
            if (readFile.exists() && readFile.isFile()) {
                try {
                    BufferedReader br = new BufferedReader(new FileReader(readFile));
                    String line;
                    line = br.readLine();
                    while ((line = br.readLine()) != null) {
                        String[] elementos = line.split(",");
                        String[] autores = elementos[0].split("#");
                        String titulo = elementos[1];
                        String[] keywords = elementos[2].split("#");
                        int anoPub;
                        int dimensao;
                        try {
                            anoPub = Integer.parseInt(elementos[3]);
                        } catch (NumberFormatException e) {
                            System.out.printf("Erro no ano do capítulo de livro com título \"%s\"\n.", titulo);
                            continue;
                        }
                        try {
                            dimensao = Integer.parseInt(elementos[4]);
                        } catch (NumberFormatException e) {
                            System.out.printf("Erro na dimensão do capítulo de livro com título \"%s\"\n.", titulo);
                            continue;
                        }
                        String resumo = elementos[5];
                        String autora = elementos[6];
                        String isbn = elementos[7];
                        String nomeCap = elementos[8];
                        int pagI;
                        try {
                            pagI = Integer.parseInt(elementos[9]);
                        } catch (NumberFormatException e) {
                            System.out.printf("Erro na página inicial do capítulo de livro com título \"%s\"\n.",
                                    titulo);
                            continue;
                        }
                        int pagF;
                        try {
                            pagF = Integer.parseInt(elementos[10]);
                        } catch (NumberFormatException e) {
                            System.out.printf("Erro na página final do capítulo de livro com título \"%s\"\n.", titulo);
                            continue;
                        }
                        LivroCapitulo newLivroCap = new LivroCapitulo(nomeCap, pagI, pagF, autora, isbn, autores,
                                titulo, keywords, anoPub, dimensao, resumo);
                        cisuc.addPub(newLivroCap, true);
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
        } else if (escolha == 0) {
            ArrayList<Grupo> listaGrupos = new ArrayList<>();
            ArrayList<Investigador> listaInvest = new ArrayList<>();
            ArrayList<Publicacao> listaPub = new ArrayList<>();
            try {
                ObjectInputStream ois = new ObjectInputStream(new FileInputStream("Grupos.obj"));
                listaGrupos = (ArrayList<Grupo>) ois.readObject();
                ois.close();
            } catch (FileNotFoundException ex) {
                System.out.println("Erro a abrir ficheiro.");
            } catch (IOException ex) {
                System.out.println("Erro a ler ficheiro.");
            } catch (ClassNotFoundException ex) {
                System.out.println("Erro a converter objeto.");
            }

            try {
                ObjectInputStream ois = new ObjectInputStream(new FileInputStream("Investigadores.obj"));
                listaInvest = (ArrayList<Investigador>) ois.readObject();
                ois.close();
            } catch (FileNotFoundException ex) {
                System.out.println("Erro a abrir ficheiro.");
            } catch (IOException ex) {
                System.out.println("Erro a ler ficheiro.");
            } catch (ClassNotFoundException ex) {
                System.out.println("Erro a converter objeto.");
            }

            try {
                ObjectInputStream ois = new ObjectInputStream(new FileInputStream("Publicacoes.obj"));
                listaPub = (ArrayList<Publicacao>) ois.readObject();
                ois.close();
            } catch (FileNotFoundException ex) {
                System.out.println("Erro a abrir ficheiro.");
            } catch (IOException ex) {
                System.out.println("Erro a ler ficheiro.");
            } catch (ClassNotFoundException ex) {
                System.out.println("Erro a converter objeto.");
            }
            for (Grupo newGrupo : listaGrupos) {
                cisuc.addGrupo(newGrupo);
            }
            for (Investigador newInvest : listaInvest) {
                cisuc.addMembro(newInvest, false);
            }
            for (Publicacao newPub : listaPub) {
                cisuc.addPub(newPub, false);
            }
        }
        escolha = -1;
        boolean stop = false;
        while (!stop) {
            flag = false;
            while (!flag) {
                System.out.println();
                System.out.printf("""
                        # - Menu - #
                        1 - Indicadores Gerais do CISUC
                        2 - Listar Publicações de um Grupo (últimos 5 anos)
                        3 - Listar Elementos de um Grupo por Categoria
                        4 - Listar Publicações de um Investigador
                        5 - Listar Grupos de Investigação
                        0 - Terminar (Gravar Base de Dados)
                        Seleção -> """);
                System.out.printf(" ");
                if (input.hasNextInt()) {
                    escolha = input.nextInt();
                    if (escolha <= 6 && escolha >= 0) {
                        flag = true;
                    } else {
                        System.out.printf("Escolha inválida.");
                    }
                } else {
                    System.out.printf("Escolha inválida.");
                }
                input.nextLine();
            }
            System.out.println();
            switch (escolha) {
                case 1:
                    System.out.println("Indicadores gerais da CISUC:");
                    System.out.printf("Número de membros CISUC: %d\n", cisuc.totalMembers());
                    System.out.println("---------------------------");
                    System.out.printf("Número de Efetivos: %d\nNúmero de Estudantes: %d\n", cisuc.totalCategory()[0],
                            cisuc.totalCategory()[1]);
                    System.out.println("---------------------------");
                    System.out.printf("Total de Publicações nos últimos 5 anos: %d\n", cisuc.pubFive());
                    System.out.println("---------------------------");
                    System.out.printf(
                            "Artigos de Conferência: %d\nArtigos de Revista: %d\nLivros: %d\nLivros de Conferência: %d\nCapítulos de Livros: %d\n",
                            cisuc.pubCategory()[0], cisuc.pubCategory()[1], cisuc.pubCategory()[2],
                            cisuc.pubCategory()[3], cisuc.pubCategory()[4]);
                    break;
                case 2:
                    String acronimo = "";
                    flag = false;
                    while (!flag) {
                        System.out.printf("Introduza o Acrónimo do Grupo -> ");
                        if (input.hasNextLine()) {
                            acronimo = input.nextLine();
                            if (acronimo.length() <= 6 && acronimo.length() > 0) {
                                flag = true;
                            } else {
                                System.out.println("Acrónimo inválido.");
                            }
                        } else {
                            System.out.println("Acrónimo inválido.");
                        }
                    }
                    ArrayList<Publicacao> lista = cisuc.showPubGrupo(acronimo);
                    if (lista != null) {
                        Collections.sort(lista, Publicacao.anoOrganiza);
                        System.out.printf("Lista de Publições organizada por ano:\n");
                        for (Publicacao pub : lista) {
                            System.out.printf("  ");
                            System.out.println(pub);
                        }
                        Collections.sort(lista, Publicacao.impactoOrganiza);
                        System.out.printf("Lista de Publições organizada por impacto:\n");
                        for (Publicacao pub : lista) {
                            System.out.printf("  ");
                            System.out.println(pub);
                        }
                        Collections.sort(lista, Publicacao.tipoOrganiza);
                        System.out.printf("Lista de Publições organizada por tipo:\n");
                        for (Publicacao pub : lista) {
                            System.out.printf("  ");
                            System.out.println(pub);
                        }
                    }
                    break;

                case 3:
                    acronimo = "";
                    flag = false;
                    while (!flag) {
                        System.out.printf("Introduza o Acrónimo do Grupo -> ");
                        if (input.hasNextLine()) {
                            acronimo = input.nextLine();
                            if (acronimo.length() <= 6 && acronimo.length() > 0) {
                                flag = true;
                            } else {
                                System.out.println("Acrónimo inválido.");
                            }
                        } else {
                            System.out.println("Acrónimo inválido.");
                        }
                    }
                    ArrayList<Investigador> listaInvest = cisuc.showInvesGrupo(acronimo);
                    if (listaInvest != null) {
                        Collections.sort(listaInvest, Investigador.investOrganiza);
                        for (Investigador invest : listaInvest) {
                            System.out.println(invest);
                        }
                    }
                    break;

                case 4:
                    String nome = "";

                    System.out.printf("Introduza o Nome do Investigador -> ");
                    nome = input.nextLine();
                    lista = cisuc.showPubInvest(nome);
                    if (lista != null) {
                        Collections.sort(lista, Publicacao.anoOrganiza);
                        System.out.printf("Lista de Publições organizada por ano:\n");
                        for (Publicacao pub : lista) {
                            System.out.printf("  ");
                            System.out.println(pub);
                        }
                        Collections.sort(lista, Publicacao.tipoOrganiza);
                        System.out.printf("Lista de Publições organizada por tipo:\n");
                        for (Publicacao pub : lista) {
                            System.out.printf("  ");
                            System.out.println(pub);
                        }
                        Collections.sort(lista, Publicacao.impactoOrganiza);
                        System.out.printf("Lista de Publições organizada por impacto:\n");
                        for (Publicacao pub : lista) {
                            System.out.printf("  ");
                            System.out.println(pub);
                        }
                    }
                    break;

                case 5:
                    for (Grupo showGrupo : cisuc.getGruposCisuc()) {
                        System.out.println(showGrupo);
                    }
                    acronimo = "";
                    flag = false;
                    while (!flag) {
                        System.out.printf("Introduza o Acrónimo do Grupo -> ");
                        if (input.hasNextLine()) {
                            acronimo = input.nextLine();
                            if (acronimo.length() <= 6 && acronimo.length() > 0) {
                                flag = true;
                            } else {
                                System.out.println("Acrónimo inválido.");
                            }
                        } else {
                            System.out.println("Acrónimo inválido.");
                        }
                    }
                    System.out.println();
                    for (Grupo searchGrupo : cisuc.getGruposCisuc()) {
                        if (searchGrupo.getAcronimo().toLowerCase().equals(acronimo.toLowerCase())) {
                            System.out.println(searchGrupo);
                            System.out.printf(" Número Total de Membros: %d\n",
                                    searchGrupo.totalEfetivos() + searchGrupo.totalEstudantes());
                            System.out.printf(" Número de Efetivos: %d\n Número de Estudantes: %d\n",
                                    searchGrupo.totalEfetivos(), searchGrupo.totalEstudantes());
                            ArrayList<Publicacao> listaFive = searchGrupo.pubLastFive();
                            System.out.printf(" Número de Publicações nos Últimos 5 Anos: %d\n", listaFive.size());
                            Collections.sort(listaFive, Publicacao.anoOrganiza);
                            System.out.printf(" Lista de Publições Organizada por Ano:\n");
                            for (Publicacao pub : listaFive) {
                                System.out.printf("  ");
                                System.out.println(pub);
                            }
                            Collections.sort(listaFive, Publicacao.tipoOrganiza);
                            System.out.printf(" Lista de Publições Organizada por Tipo:\n");
                            for (Publicacao pub : listaFive) {
                                System.out.printf("  ");
                                System.out.println(pub);
                            }
                            Collections.sort(listaFive, Publicacao.impactoOrganiza);
                            System.out.printf(" Lista de Publições Organizada por Impacto:\n");
                            for (Publicacao pub : listaFive) {
                                System.out.printf("  ");
                                System.out.println(pub);
                            }
                        }
                    }
                    break;

                case 0:
                    try {
                        ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("Grupos.obj"));
                        oos.writeObject(cisuc.getGruposCisuc());
                        oos.close();
                    } catch (FileNotFoundException ex) {
                        System.out.println("Erro a criar ficheiro de objetos.");
                    } catch (IOException ex) {
                        System.out.println("Erro a escrever para o ficheiro de objetos.");
                    }

                    try {
                        ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("Investigadores.obj"));
                        oos.writeObject(cisuc.getMembrosCisuc());
                        oos.close();
                    } catch (FileNotFoundException ex) {
                        System.out.println("Erro a criar ficheiro de objetos.");
                    } catch (IOException ex) {
                        System.out.println("Erro a escrever para o ficheiro de objetos.");
                    }

                    try {
                        ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("Publicacoes.obj"));
                        oos.writeObject(cisuc.getPubCisuc());
                        oos.close();
                    } catch (FileNotFoundException ex) {
                        System.out.println("Erro a criar ficheiro de objetos.");
                    } catch (IOException ex) {
                        System.out.println("Erro a escrever para o ficheiro de objetos.");
                    }
                    stop = true;
                    break;
            }
        }
    }
}
