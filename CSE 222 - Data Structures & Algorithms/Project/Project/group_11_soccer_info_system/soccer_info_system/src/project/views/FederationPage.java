package project.views;

import java.util.Scanner;

import project.models.Federation;

public class FederationPage extends Page {
	Federation federation;
	Scanner scnnr;
	
	public FederationPage(Scanner scnnr, Federation federation) {
		this.scnnr = scnnr;
		this.federation = federation;
	}
}
