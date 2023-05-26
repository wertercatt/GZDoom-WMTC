// Simple DECORATE to ZScript converter for GZDoom developers
// Written by RACCOON to help with MEMBRANE development, among other things
// ----------------
// Feel free to like, do whatever with this, like use the code for things,
// or take over the project and update it, I don't care.
// Just don't say you wrote it or something...

package com.raccoondev.dectozsc;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
//import java.lang.StringBuilder;
import java.io.FileWriter;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

public class DECtoZSC {
	// This is supposed to load a .dec file, make the changes needed from DECORATE to ZScript, and output a .zsc file.
	
	public static void main(String[] args) throws IOException {
		boolean debug = false;
		boolean nofile = false;
		boolean noext = false;
		boolean printhelp = false;
		
		for(int i = 0; i < args.length; i++) {
			if(args.length > 2 && args[i].equalsIgnoreCase("-help")) printhelp = true; // -help - print the help and ignore everything else
			if(args.length > 2 && args[i].equalsIgnoreCase("-nofile")) nofile = true; // -nofile - don't make a file
			if(args.length > 2 && args[i].equalsIgnoreCase("-debug")) debug = true; // -debug - output everything being done to the command line
			if(args.length > 2 && args[i].equalsIgnoreCase("-noext")) noext = true; // -noext - don't bother with the extension
		}
		
	// Load .dec file into a Scanner because lazy
		Scanner dec = null;
		
		try {
			File dec_file = new File(args[0]);
			dec = new Scanner(dec_file);
		} catch (FileNotFoundException e) {
			System.out.println("I don't know what the fuck you're trying to do but that's not a .dec file.");
			System.exit(0); // I'm not going to bother being all robust and shit with this.
		}
		
		// Create a .zsc file to write to
		FileWriter zsc_file = null;
		if(!nofile) {
			try {
				zsc_file = new FileWriter(args[0].substring(0, args[0].length()-3) + "zsc");
			} catch (IOException ex) {
				Logger.getLogger(DECtoZSC.class.getName()).log(Level.SEVERE, null, ex);
				System.out.println("Your computer has randomly decided to not let me make a .zsc file.");
				System.exit(0); // I'm not going to bother being all robust and shit with this.
			}
		}
		
	// Parser
		String line;
	//	boolean insideActor = false;
		boolean insideDefaults = false;
		boolean insideStates = false;
		boolean insideState = false;
		boolean encounteredText;
		boolean lineComment;
		boolean blockComment = false;
		boolean classDeclaration;
		boolean derivedClass;
		byte countSpaces;
		
		StringBuilder zline;
		int indentLevel = 0;
		boolean indentUp; // Indent up on next line
		boolean semicolon;
		boolean nosemicolon; // Because sometimes it doesn't get the message and I'm not going to bother to find out why.
		boolean parentheses;
		
		
		while (dec.hasNextLine()) { // Go through this line by line
			line = dec.nextLine();
			
			zline = new StringBuilder();
			
			lineComment = false;
			encounteredText = false;
			indentUp = false;
			semicolon = false;
			nosemicolon = false;
			countSpaces = 0;
			classDeclaration = false;
			derivedClass = false;
			
			if(insideDefaults) {
				if(line.toUpperCase().contains("STATES") || line.toUpperCase().contains("}")) {
					if(!nofile) zsc_file.write("	}\n");
					indentLevel -= 1;
					insideDefaults = false;
					
					semicolon = false;
					nosemicolon = true; // quick, dirty fix

					if(debug) {
						System.out.println("	}");
						try {
							Thread.sleep(1); // Workaround for Java not always printing before errors
						} catch (InterruptedException e) {
							// I don't know what the fuck you're doing if this happens.
						}
					}
				} else { // Workaround for the people who think that putting brackets on the next line is somehow a good idea
					line = line.replace('{',' ');
				}
			}
			
			// step through char by char
			for(int i = 0; i < line.length() && !lineComment; i++) {
			// -- COMMENTS --
				if(line.charAt(i) == '/') { // Comment: copy the rest verbatim.
					if(line.charAt(i+1) == '/') { // LINE COMMENT
						lineComment = true;
						
					// WIPE THE LINE OUT HERE
						// Add Semicolon and maybe Parentheses
						if(semicolon &! nosemicolon) {
							if(line.charAt(i-1) == ' ' || line.charAt(i-1) == '\t') { // Usually people have a space between the last thing and the comment
								if(insideState && countSpaces > 2 && line.charAt(i-1) != ')') {
									if( // Make sure it's not a keyword
											!(line.toUpperCase().contains("BRIGHT") && line.toUpperCase().indexOf("BRIGHT", 5) > (i-10)) &&
											!(line.toUpperCase().contains("NODELAY") && line.toUpperCase().indexOf("NODELAY", 5) > (i-10))
											) {
										zline.append("()");
									}
								}
								zline.append(';');
							} else { // If not... don't worry about it.
								if(insideState && countSpaces > 2 && line.charAt(i-1) != ')') {
									if( // Make sure it's not a keyword
											!(line.toUpperCase().contains("BRIGHT") && line.toUpperCase().indexOf("BRIGHT", 5) > (i-10)) &&
											!(line.toUpperCase().contains("CANRAISE") && line.toUpperCase().indexOf("CANRAISE", 5) > (line.length()-14)) &&
											!(line.toUpperCase().contains("FAST") && line.toUpperCase().indexOf("FAST", 5) > (line.length()-8)) &&
											!(line.toUpperCase().contains("NODELAY") && line.toUpperCase().indexOf("NODELAY", 5) > (line.length()-12)) &&
											!(line.toUpperCase().contains("SLOW") && line.toUpperCase().indexOf("SLOW", 5) > (line.length()-8))
											) {
										zline.append("()");
									}
								}
								zline.append(';');
							}
						//	semicolon = false;
						//	nosemicolon = true;
							// Unneeded?
						}
						
						zline.append(line.substring(i));
					} else if(line.charAt(i+1) == '*') { // BLOCK COMMENT
						blockComment = true;
					}
				}
				if(blockComment) {
					if(line.charAt(i) == '*' && line.charAt(i+1) =='/') {
						zline.append("*/");
						i += 2;
						blockComment = false;
						
						if(i == line.length()) lineComment = true; // Because usually there's nothing after it.
					} else {
						zline.append(line.charAt(i));
					}
				}
				
				if(!lineComment && !blockComment) {
				// -- OPEN BRACKET --
					if(line.charAt(i) == '{') {
						indentUp = true;
						semicolon = false;
						nosemicolon = true; // quick, dirty fix
					}
				// -- CLOSE BRACKET --
					if(line.charAt(i) == '}') {
						indentLevel -= 1;
						semicolon = false;
						nosemicolon = true;

						if(insideState) {
							indentLevel -= 1;
							insideState = false;
						}
					}

					if(indentLevel > 0) { // If you're in an actor...
							// -- STATE DECLARATION --
							if(line.charAt(i) == ':') {
								indentUp = true;
								semicolon = false;
								if(insideState) { // Are you already in a state?
									indentLevel -= 1; // Drop down for a sec
								} else {
									insideState = true; // be in one
								}
							}

							if(line.charAt(i) != '\t') { // Ignore tabs
								if(!encounteredText) {
									if(line.charAt(i) != ' ') {
										encounteredText = true;
										semicolon = true;
										zline.append(line.charAt(i));
									}
								} else {
									if(line.charAt(i) == ' ') countSpaces+=1;
									zline.append(line.charAt(i));
								}
							}
					} else { // Actor Declaration Bullshit
						if(classDeclaration) {
							if(line.charAt(i) == '{') {
								if(!derivedClass) zline.append(": ACTOR ");
								indentUp = true;
							} else if(line.length() == i+1 || (line.charAt(i+1) == '/' && line.charAt(i+2) == '/')) {
								 // Workaround for the people who think that putting brackets on the next line is somehow a good idea
								if(line.length() == i+1) {
									zline.append(line.charAt(i));
									line = line.substring(0, line.length()-1).concat(" ");
								}
								if(!derivedClass) zline.append(" : ACTOR {");
								else zline.append(" {");
								indentUp = true;
							}
							
							zline.append(line.charAt(i));
							if(line.charAt(i) == ':') {
								derivedClass = true;
							}

						} else {
							if(line.toUpperCase().contains("ACTOR")) {
								zline.append("CLASS");
								i += 4;
								classDeclaration = true;
							} else { // IDK, just like, copy it verbatim... :V
								zline.append(line.charAt(i));
							}
						}
					}
				}
			}

			if(!lineComment && !blockComment) { // if you had a line-comment this already happened.  If you're in a block comment you're just kinda fucked here.
				// Add Semicolon and maybe Parentheses
				if(semicolon &! nosemicolon) {
					if(insideState && countSpaces > 2 && line.charAt(line.length()-1) != ')') {
						if( // Make sure it's not a keyword
								!(line.toUpperCase().contains("BRIGHT") && line.toUpperCase().indexOf("BRIGHT", 5) > (line.length()-8)) &&
								!(line.toUpperCase().contains("CANRAISE") && line.toUpperCase().indexOf("CANRAISE", 5) > (line.length()-14)) &&
								!(line.toUpperCase().contains("FAST") && line.toUpperCase().indexOf("FAST", 5) > (line.length()-8)) &&
								!(line.toUpperCase().contains("NODELAY") && line.toUpperCase().indexOf("NODELAY", 5) > (line.length()-12)) &&
								!(line.toUpperCase().contains("SLOW") && line.toUpperCase().indexOf("SLOW", 5) > (line.length()-8))
								) {
							zline.append("()");
						}
					}
					zline.append(';');
				}
			}

			// Indent it all
			for(int j = 0; j < indentLevel; j++) {
				zline.insert(0, '\t');
			}
			if(indentUp) {
				indentLevel += 1;
				indentUp = false;
			}
			
			// WRITE
			if(!nofile) zsc_file.write(zline.toString());
			if(!nofile) zsc_file.write('\n');
			
			if(debug) {
				System.out.println(zline.toString());
				try {
					Thread.sleep(1); // Workaround for Java not always printing before errors
				} catch (InterruptedException e) {
					// I don't know what the fuck you're doing if this happens.
				}
			}
			
			if(classDeclaration) { // If this line was a class declaration, we need to set up the Default block!
				if(!nofile) zsc_file.write("	Default {\n");
				indentLevel += 1;
				insideDefaults = true;
				classDeclaration = false;
				
				if(debug) {
					System.out.println("	Default {");
				}
			}
			
			if(!nofile) zsc_file.flush(); // Make sure you keep writing it!
			if(debug) System.out.flush(); // Here too!
		}
		
	// Close the .zsc file
		if(!nofile) zsc_file.close();
	}
}
