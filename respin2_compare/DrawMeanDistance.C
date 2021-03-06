  
vector< pair<TString,TString> > fSets ={ {"dit","reg_5bpm"},
					 {"dit","lagr_6bpm"},
					 {"dit","lagr_all"},
					 {"dit","reg_all"},
					 {"reg_5bpm","reg_6bpm"},
					 {"reg_5bpm","reg_all"},
					 {"lagr_6bpm","reg_6bpm"},
					 {"lagr_all","reg_all"},
					 {"lagr_6bpm","lagr_all"},
					 {"lagr_all_trunc","lagr_all"}};


void DrawMeanDistance(){
  vector<Double_t> fDeltaMu_slug;
  vector<Double_t> fSigmaDeltaMu_slug;
  vector<Double_t> fChiSquare_slug;
  vector<Int_t> fNDF_slug;
  vector<Double_t> fProb_slug;
  
  vector<Double_t> fDeltaMu_slugfix;
  vector<Double_t> fSigmaDeltaMu_slugfix;
  vector<Double_t> fChiSquare_slugfix;
  vector<Int_t> fNDF_slugfix;
  vector<Double_t> fProb_slugfix;
  
  gStyle->SetOptFit(1);
  gStyle->SetStatY(0.9);
  TCanvas *c1 = new TCanvas("c1","c1",1400,600);
  // c1->SetGridx();
  // c1->SetGridy();
  c1->cd();
  TPad *pad1 = new TPad("","",0,0,0.66,1.0);
  TPad *pad2 = new TPad("","",0.66,0,1.0,1.0);
  pad1->Draw();
  pad2->Draw();
  pad1->SetGridx();
  pad1->SetGridy();
  TCanvas *c2 = new TCanvas("c2","c2",1400,600);
  c2->SetGridy();
  c2->SetGridx();
  auto iter= fSets.begin();
  while(iter!= fSets.end()){
    TString set1 = (*iter).first;
    TString set2 = (*iter).second;
    TF1 *fp0fix = new TF1("fp0fix","[0]",-100,100);
    TF1 *fp0free = new TF1("fp0free","[0]",-100,100);
    fp0fix->FixParameter(0,0);
    
    TFile *input =  TFile::Open(Form("./rootfiles/prex_minidiff_%s_%s.root",set1.Data(),set2.Data()));
    TTree *slug_tree = (TTree*)input->Get("slug");
    // c2->cd(1);
    // TMultiGraph *mg_diff = new TMultiGraph();
    // TLegend *leg_diff = new TLegend(0.99,0.9,0.9,0.7);
    // slug_tree->Draw("sign*delta_Adet:slug+arm_flag/6","","goff");
    // TGraph* gdiff = new TGraph(slug_tree->GetSelectedRows(),slug_tree->GetV2(),slug_tree->GetV1());
    // gdiff->SetLineColor(kBlack);
    // gdiff->SetMarkerColor(kBlack);
    // gdiff->SetMarkerStyle(20);
    // mg_diff->Add(gdiff,"lp");
    // leg_diff->AddEntry(gdiff,"both-arm","p");
    
    // slug_tree->Draw("sign*delta_Adet:slug+arm_flag/6","arm_flag==2","goff");
    // TGraph* gdelta_l = new TGraph(slug_tree->GetSelectedRows(),slug_tree->GetV2(),slug_tree->GetV1());
    // gdelta_l->SetMarkerColor(kRed);
    // gdelta_l->SetMarkerStyle(20);
    // mg_diff->Add(gdelta_l,"p");
    // leg_diff->AddEntry(gdelta_l,"left-arm","p");
    
    // slug_tree->Draw("sign*delta_Adet:slug+arm_flag/6","arm_flag==1","goff");
    // TGraph* gdelta_r = new TGraph(slug_tree->GetSelectedRows(),slug_tree->GetV2(),slug_tree->GetV1());
    // gdelta_r->SetMarkerColor(kBlue);
    // gdelta_r->SetMarkerStyle(20);
    // mg_diff->Add(gdelta_r,"p");
    // leg_diff->AddEntry(gdelta_r,"right-arm","p");

    // mg_diff->Draw("A");
    // mg_diff->SetTitle(Form(" %s vs %s : Sign Corrected #LT#Delta A#GT (ppb) vs Slug; Slug; #Delta A(ppb) ",
    // 			   set1.Data(),set2.Data()));
    // mg_diff->GetXaxis()->SetTitleSize(0.07);
    // mg_diff->GetXaxis()->SetTitleOffset(0.5);
    // mg_diff->GetYaxis()->SetTitleSize(0.07);
    // mg_diff->GetYaxis()->SetTitleOffset(0.5);
    // leg_diff->Draw("same");
    c2->cd();
    TMultiGraph *mg_dist = new TMultiGraph();
    TLegend *leg_dist = new TLegend(0.99,0.9,0.9,0.7);
    slug_tree->Draw("dist_Adet:slug+arm_flag/6","","goff");
    TGraph* gdist = new TGraph(slug_tree->GetSelectedRows(),slug_tree->GetV2(),slug_tree->GetV1());
    gdist->SetLineColor(kBlack);
    gdist->SetMarkerColor(kBlack);
    gdist->SetMarkerStyle(20);
    mg_dist->Add(gdist,"lp");
    leg_dist->AddEntry(gdist,"both-arm","p");
    
    slug_tree->Draw("dist_Adet:slug+arm_flag/6","arm_flag==2","goff");
    TGraph* gdist_l = new TGraph(slug_tree->GetSelectedRows(),slug_tree->GetV2(),slug_tree->GetV1());
    gdist_l->SetMarkerColor(kRed);
    gdist_l->SetMarkerStyle(20);
    mg_dist->Add(gdist_l,"p");
    leg_dist->AddEntry(gdist_l,"left-arm","p");
    
    slug_tree->Draw("dist_Adet:slug+arm_flag/6","arm_flag==1","goff");
    TGraph* gdist_r = new TGraph(slug_tree->GetSelectedRows(),slug_tree->GetV2(),slug_tree->GetV1());
    gdist_r->SetMarkerColor(kBlue);
    gdist_r->SetMarkerStyle(20);
    mg_dist->Add(gdist_r,"p");
    leg_dist->AddEntry(gdist_r,"right-arm ","p");
    
    mg_dist->Draw("A");
    mg_dist->SetTitle(Form(" %s vs %s : #sqrt{ #LT(#Delta A )^{2}#GT } (ppb) vs Slug; Slug; #sqrt{ #LT(#Delta A )^{2}#GT } (ppb) ",
			   set1.Data(),set2.Data()));
    mg_dist->GetXaxis()->SetTitleSize(0.07);
    mg_dist->GetXaxis()->SetTitleOffset(0.5);
    mg_dist->GetYaxis()->SetTitleSize(0.07);
    mg_dist->GetYaxis()->SetTitleOffset(0.5);
    leg_dist->Draw("same");
    c2->SaveAs(Form("./plots/delta_A_rms_%s_%s_by_slug.png",
		    set1.Data(),set2.Data()));


    pad1->cd();
    TMultiGraph *mg_er = new TMultiGraph();
    TLegend *leg_er = new TLegend(0.99,0.9,0.9,0.7);
    slug_tree->Draw("sign*delta_Adet:delta_Adet_err:slug+arm_flag/6","","goff");
    // pretending it is both-only...
    TGraphErrors* ger_both = new TGraphErrors(slug_tree->GetSelectedRows(),
					 slug_tree->GetV3(),slug_tree->GetV1(),
					 0,slug_tree->GetV2());
    
    ger_both->Fit("fp0free","Q");  
    double* yval = slug_tree->GetV1();
    double* yerr = slug_tree->GetV2();
    int ynpt = slug_tree->GetSelectedRows();
    TH1D *hpull_free = new TH1D("hpull_free","Pull Fit",40,-5,8);
    TH1D *hpull_fixed = new TH1D("hpull_fixed","Pull Fit",40,-5,8);
    double mean = fp0free->GetParameter(0);
    for(int i=0;i<ynpt;i++){
      hpull_free->Fill((yval[i]-mean)/yerr[i]);
      hpull_fixed->Fill(yval[i]/yerr[i]);
    }
    hpull_free->Fit("gaus","Q");
    hpull_fixed->Fit("gaus","Q");
    hpull_free->SetName("Pull");
    hpull_fixed->SetName("Pull");
    
    slug_tree->Draw("sign*delta_Adet:delta_Adet_err:slug+arm_flag/6","arm_flag==1","goff");
    TGraphErrors* ger_right = new TGraphErrors(slug_tree->GetSelectedRows(),
					      slug_tree->GetV3(),slug_tree->GetV1(),
					      0,slug_tree->GetV2());
    slug_tree->Draw("sign*delta_Adet:delta_Adet_err:slug+arm_flag/6","arm_flag==2","goff");
    TGraphErrors* ger_left = new TGraphErrors(slug_tree->GetSelectedRows(),
					      slug_tree->GetV3(),slug_tree->GetV1(),
					      0,slug_tree->GetV2());
    
    ger_both->SetLineColor(kBlack);
    ger_both->SetMarkerColor(kBlack);
    ger_both->SetMarkerStyle(20);
    ger_right->SetLineColor(kBlue);
    ger_right->SetMarkerColor(kBlue);
    ger_right->SetMarkerStyle(20);
    ger_left->SetLineColor(kRed);
    ger_left->SetMarkerColor(kRed);
    ger_left->SetMarkerStyle(20);
    
    mg_er->Add(ger_both,"p");
    mg_er->Add(ger_right,"p");
    mg_er->Add(ger_left,"p");
    leg_er->AddEntry(ger_both,"both-arm","p");
    leg_er->AddEntry(ger_right,"right-arm","p");
    leg_er->AddEntry(ger_left,"left-arm","p");
    pad1->cd();
    mg_er->Draw("A");
    // ger_both->Fit("fp0free","Q");  
    leg_er->Draw("same");
    mg_er->SetTitle(Form(" %s vs %s :Sign Corrected  #Delta A #pm #sigma(#Delta A) (ppb) vs Slug; Slug; #Delta A (ppb) ",
			   set1.Data(),set2.Data()));
    mg_er->GetXaxis()->SetTitleSize(0.07);
    mg_er->GetXaxis()->SetTitleOffset(0.5);
    mg_er->GetYaxis()->SetTitleSize(0.07);
    mg_er->GetYaxis()->SetTitleOffset(0.5);
    double ymax = mg_er->GetYaxis()->GetXmax();
    double ymin = mg_er->GetYaxis()->GetXmin();
    mg_er->GetYaxis()->SetRangeUser(ymin,ymax+0.3*(ymax-ymin));
    gPad->Update();
    TPaveStats *ps = (TPaveStats*)ger_both->FindObject("stats");
    ps->SetX2NDC(0.9);
    pad2->cd();

    gStyle->SetOptFit(0);
    gStyle->SetOptStat(0);
    hpull_free->Draw();
    // pad2->Update();
    // TPaveStats *pspull_free = (TPaveStats*)hpull_free->FindObject("stats");
    // pspull_free->SetOptStat(111111);
    // pspull_free->SetY1NDC(0.5);
    // pspull_free->SetX1NDC(0.5);
    fDeltaMu_slug.push_back(fp0free->GetParameter(0));
    fSigmaDeltaMu_slug.push_back(fp0free->GetParError(0));
    fChiSquare_slug.push_back(fp0free->GetChisquare());
    fProb_slug.push_back(fp0free->GetProb());
    fNDF_slug.push_back(fp0free->GetNDF());

    TLatex *text_mean = new TLatex(2,11,Form("mean=%.2f #pm %.2f",
					      hpull_free->GetFunction("gaus")->GetParameter(1),
					      hpull_free->GetFunction("gaus")->GetParError(1)));

    TLatex *text_sigma = new TLatex(3,10,Form("#sigma=%.2f #pm %.2f",
					      hpull_free->GetFunction("gaus")->GetParameter(2),
					      hpull_free->GetFunction("gaus")->GetParError(2)));
    TLatex *text_chi = new TLatex(3,9,Form("#chi^{2}=%.2f/%d",
					    hpull_free->GetFunction("gaus")->GetChisquare(),
					    hpull_free->GetFunction("gaus")->GetNDF()));

    TLatex *text_entries = new TLatex(3,12,Form("Entries:  %.0f",
						hpull_free->GetEntries()));
    text_mean->Draw("same");
    text_chi->Draw("same");
    text_entries->Draw("same");
    text_sigma->Draw("same");
    c1->SaveAs(Form("./plots/delta_A_freepar_fit_%s_%s_by_slug.png",set1.Data(),set2.Data()));
    gStyle->SetOptFit(1);
    gStyle->SetOptStat(1);
    
    pad1->cd();
    ger_both->Fit("fp0fix","Q");
    fDeltaMu_slugfix.push_back(fp0fix->GetParameter(0));
    fSigmaDeltaMu_slugfix.push_back(fp0fix->GetParError(0));
    fChiSquare_slugfix.push_back(fp0fix->GetChisquare());
    fNDF_slugfix.push_back(fp0fix->GetNDF());
    fProb_slugfix.push_back(fp0fix->GetProb());
    pad2->cd();
    hpull_fixed->Draw();
    pad2->Update();
    TPaveStats *pspull_fixed = (TPaveStats*)hpull_fixed->FindObject("stats");
    pspull_fixed->SetOptStat(111111);
    pspull_fixed->SetY1NDC(0.5);
    pspull_fixed->SetX1NDC(0.5);
    c1->SaveAs(Form("./plots/delta_A_fixpar_fit_%s_%s_by_slug.png",set1.Data(),set2.Data()));
    
    input->Close();
    iter++;
  } // end of iteration comparison sets

  cout << " ********* Slug Summary ************ " << endl;
  Int_t icount=0;
  iter = fSets.begin();
  while(iter!= fSets.end()){
    TString set1 = (*iter).first;
    TString set2 = (*iter).second;
    set1.ReplaceAll("_","\\_");
    set2.ReplaceAll("_","\\_");
    cout << set1 <<  " vs " << set2 << "&";
    printf("%.1f & %.1f & %.1f & %d & %.2f \\\\ \n",
	   fDeltaMu_slug[icount],fSigmaDeltaMu_slug[icount],
	   fChiSquare_slug[icount],fNDF_slug[icount],fProb_slug[icount]);
    iter++;
    icount++;
  }
  cout << " ********* fix para " << endl;
  icount=0;
  iter = fSets.begin();
  while(iter!= fSets.end()){
    TString set1 = (*iter).first;
    TString set2 = (*iter).second;
    set1.ReplaceAll("_","\\_");
    set2.ReplaceAll("_","\\_");
    cout << set1 <<  " vs " << set2 << "&";
    printf("%.0f & %.0f & %.1f & %d & %.2f \\\\ \n",
	   fDeltaMu_slugfix[icount],fSigmaDeltaMu_slugfix[icount],
	   fChiSquare_slugfix[icount],fNDF_slugfix[icount],fProb_slugfix[icount]);
    iter++;
    icount++;
  }
}
