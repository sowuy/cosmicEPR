import sys, os
from array import array
from MuonAnalysis.Cosmics.ROOTTools import *
from bins import make_bins

tdr_style()
ROOT.gStyle.SetOptStat(111111)
ROOT.gStyle.SetOptFit(1111)

def fit_histo(h, hist_name, draw=False):
    if '_test' in hist_name:
        factor = 2.5 # mean +/- 1.5 * rms
        hist_name = hist_name.replace('_test','')        
    if '_fixed' in hist_name:
        factor = 99.9 # mean +/- 1.5 * rms
        hist_name = hist_name.replace('_fixed','')
        print h     
    elif 'P' in hist_name: # pull
        factor = 3/(h.GetRMS() if h.GetRMS() > 0 else 1) # fix to mean +/- 3
    elif 'R' in hist_name or 'D' in hist_name:
        factor = 1.5 # mean +/- 1.5 * rms
    else:
        raise NotImplementedError('fit_histo with hist_name %s' % hist_name)
    opt = 'qrll'
    if not draw:
        opt += '0'
    original_range = None
    original_prob = None
    original_mu = None
    original_sigma = None
    refit_count = 0
    while 1:
        if factor == 99.9:
            i=[0]
            core_mean  = h.GetMean()
            core_width = factor*h.GetRMS()
            fcn = ROOT.TF1('core%i' % i[0], 'gaus', core_mean - core_width, core_mean + core_width)
            i[0] += 1
            h.Fit(fcn, 'qrll')
            res = {
        'fcn': fcn,
        'constant': (fcn.GetParameter(0), fcn.GetParError(0)),
        'mu':       (fcn.GetParameter(1), fcn.GetParError(1)),
        'sigma':    (fcn.GetParameter(2), fcn.GetParError(2)),
        }
        else:
            res = fit_gaussian(h, factor, opt)
        if original_range is None:
            original_range = res['fcn'].GetXmin(), res['fcn'].GetXmax()
            original_prob = res['fcn'].GetProb()
            original_mu = res['mu']
            original_sigma = res['sigma']
        if res['fcn'].GetProb() > 0.03:
            break
        refit_count += 1
        if refit_count >= 5:
            break
        factor *= 0.9
    res['original_range'] = original_range
    res['original_prob'] = original_prob
    res['original_mu'] = original_mu
    res['original_sigma'] = original_sigma
    res['refit_count'] = refit_count
    return res

def get_histo_stat(h, hist_name, stat):
    if stat == 'rms':
        return h.GetRMS(), h.GetRMSError()
    elif stat == 'mean':
        return h.GetMean(), h.GetMeanError()
    elif stat == 'sigma':
        return fit_histo(h, hist_name)['sigma']
    elif stat == 'under':
        return h.GetBinContent(0), 0
    elif stat == 'over':
        return h.GetBinContent(h.GetNbinsX()+1), 0
    elif stat == 'out':
        u,ue = get_histo_stat(h, hist_name, 'under')
        o,oe = get_histo_stat(h, hist_name, 'over')
        return u+o, 0
    raise NotImplementedError('get_histo_stat for %s' % stat)
                   
class Drawer:
    tracks = [
        'Global',
        'TPFMS',
        'TkOnly',
        'Picky',
        'DYT',
        'OldTuneP',
        'TuneP'
        ]

    nice_names = {
        'Global': 'Global',
        'TkOnly': 'Tracker-only',
        'TPFMS': 'TPFMS',
        'Picky': 'Picky',
        'DYT': 'DYT',
        'TuneP': 'Tune P',
        'OldTuneP': 'Old Tune P',
        'StAlone': 'Standalone'
        }
    
    colors = {
        'Global': ROOT.kBlue,
        'TkOnly': ROOT.kRed,
        'TPFMS':  ROOT.kGreen+1,
        'Picky':  ROOT.kOrange+7,
        'DYT':    6,
        'TuneP':  ROOT.kBlack,
        'OldTuneP':  ROOT.kCyan,
        'StAlone':ROOT.kMagenta,
        }

    markers = {
        'Global':  21,
        'TkOnly':  20,
        'TPFMS':   22,
        'Picky':   27,
        'DYT':     30,
        'TuneP':   23,
        'OldTuneP':   25,
        'StAlone': 26,
        }

    x_titles = {
        'pt': 'ref. p_{T} (GeV)'
        }

    y_titles = {
        ('qinvpt', 'upperR1lower', 'out'):   '# over and underflows (q/p_{T} rel. res.)',
        ('qinvpt', 'upperR1lower', 'rms'):   'rms (q/p_{T} rel. residual)',
        ('qinvpt', 'upperPlower',  'rms'):   'rms (q/p_{T} pull)',
        ('qinvpt', 'upperR1lower', 'sigma'): 'Width of q/p_{T} rel. residual',
        ('qinvpt', 'upperR1lower', 'mean'): 'Mean of q/p_{T} rel. residual',
        ('qinvpt', 'upperPlower',  'sigma'): 'Width of q/p_{T} pull',
        ('qinvpt', 'upperPlower',  'mean'):  'mean (q/p_{T} pull)',
        }
    
    root_cache = []
    
    @classmethod
    def make_legend(cls, pos, tracks):
        l = ROOT.TLegend(*pos)
        l.SetTextFont(42)
        l.SetShadowColor(ROOT.kWhite)
        for t in tracks:
            e = ROOT.TLegendEntry()
            cls.root_cache.append(e)
            e.SetMarkerStyle(cls.markers[t])
            e.SetMarkerColor(cls.colors[t])
            e.SetLineColor(cls.colors[t])
            l.AddEntry(e, cls.nice_names[t], 'lpe')
        return l

    @classmethod
    def draw_legend(cls, pos, tracks):
        l = cls.make_legend(pos, tracks)
        cls.root_cache.append(l)
        l.Draw()

    def __init__(self, filename):
        self.file = ROOT.TFile(filename)

    def get_histo(self, bin_name, track, quantity, hist_name):
        return self.file.histos.Get(bin_name).Get(track).Get(quantity).Get(hist_name)

    def draw_histos(self, track, quantity, hist_name, bin_by=('pt',)):
        hs = []
        for bin in make_bins(*bin_by):
            hist = self.get_histo(bin.name, track, quantity, hist_name)
            if track == 'Global' and quantity == 'qinvpt' and hist_name == 'upperR1lower' and bin.name == 'pT350500':
                hist_name = hist_name + '_test'            
            if track == 'TuneP' and quantity == 'qinvpt' and hist_name == 'upperR1lower' and bin.name == 'pT5002000':
                hist_name = hist_name + '_fixed'            
            res = fit_histo(hist, hist_name, draw=True)
            hist_name = hist_name.replace('_test','')
            hist_name = hist_name.replace('_fixed','')
            hs.append((bin, hist, res))
        return hs
            
    def get_curve(self, track, quantity, hist_name, stat, bin_by=('pt',)):
        x, y, exl, exh, ey = [], [], [], [], []

        for bin in make_bins(*bin_by):
            if not bin.use_by_bin:
                continue

            lower, upper, abscissa = bin.main_var_range()
            x.append(abscissa)
            exl.append(abscissa - lower)
            exh.append(upper - abscissa)

            h = self.get_histo(bin.name, track, quantity, hist_name)
            if track == 'Global' and quantity == 'qinvpt' and hist_name == 'upperR1lower' and bin.name == 'pT350500':
                hist_name = hist_name + '_test'            
            if track == 'TuneP' and quantity == 'qinvpt' and hist_name == 'upperR1lower' and bin.name == 'pT5002000':
                hist_name = hist_name + '_fixed'            
            value, error = get_histo_stat(h, hist_name, stat)
            hist_name = hist_name.replace('_test','')
            hist_name = hist_name.replace('_fixed','')
            y.append(value)
            ey.append(error)

        g = ROOT.TGraphAsymmErrors(len(x), *[array('d', z) for z in (x,y,exl,exh,ey,ey)])
        g.SetTitle(';%s;%s' % (self.x_titles.get(bin_by[0], 'FIXME'), self.y_titles.get((quantity, hist_name, stat), 'FIXME')))
        g.GetYaxis().SetLabelSize(0.04)
        g.GetXaxis().SetLabelOffset(0.002)
        g.GetYaxis().SetTitleOffset(1.1)
        return g

    def overlay_curves(self, tracks, quantity, hist_name, stat, ymin, ymax, bin_by=('pt',)):
        curves = [(track, self.get_curve(track, quantity, hist_name, stat, bin_by=bin_by)) for track in tracks]

        drawopt = 'AP'
        for track, curve in curves:
            curve.SetLineColor(self.colors[track])
            curve.SetMarkerColor(self.colors[track])
            curve.SetMarkerStyle(self.markers[track])
            curve.SetMinimum(ymin)
            curve.SetMaximum(ymax)
            curve.Draw(drawopt)
            drawopt = 'P same'

        return curves

if __name__ == '__main__':
    fn = sys.argv[1]
    print fn
    fn_name = os.path.basename(fn.replace('.histos', '').replace('.root', ''))
    plot_path = os.path.join('plots/cosmicres', fn_name)

    drawer = Drawer(fn)

    for hist_name in ['upperR1lower', 'upperPlower']:
        for track in drawer.tracks:
            ps = plot_saver(os.path.join(plot_path, hist_name, track))
            for bin, hist, res in drawer.draw_histos(track, 'qinvpt', hist_name):
                hist.Draw()
                if bin.use_by_bin and res['fcn'].GetProb() < 0.03:
                    print 'check fit: prob for %s %s %s is %s' % (hist_name, track, bin.name, res['fcn'].GetProb())
                if bin.use_by_bin and res['refit_count'] > 0:
                    print 'check fit: refit count for %s %s %s is %s;\n   old range: (%10.2g, %10.2g) prob: %10.2g mu: %10.2g sigma: %10.2g\n   new range: (%10.2g, %10.2g) prob: %10.2g mu: %10.2g sigma: %10.2g' % (hist_name, track, bin.name, res['refit_count'], res['original_range'][0], res['original_range'][1], res['original_prob'], res['original_mu'][0], res['original_sigma'][0], res['fcn'].GetXmin(), res['fcn'].GetXmax(), res['fcn'].GetProb(), res['mu'][0], res['sigma'][0])
                ps.save(bin.name)

    ps = plot_saver(plot_path, log=False)

    d = drawer.file.histos.Get('copied_histograms')
    d.Get('track_multiplicity').Draw('hist text00')
    ps.save('track_multiplicity', log=True)
    d.Get('muon_multiplicity').Draw('hist text00')
    ps.save('muon_multiplicity', log=True)
    d.Get('errors').Draw('hist text00')
    ps.save('ntuple_errors')
    drawer.file.histos.Get('errors').Draw('hist text00')
    ps.save('histo_errors')

    for x in ['pT010', 'pT1020', 'pT2030', 'pT3040', 'pT4050', 'pT5075', 'pT75100', 'pT100150', 'pT150200', 'pT200350', 'pT350500', 'pT5002000', 'pTall', 'pTabove500', 'pTabove750']:
        y = drawer.file.histos.Get(x)
        if y.Get('choice_tunep_upper').GetEntries() != y.Get('choice_tunep_upper').GetBinContent(2) and y.Get('choice_tunep_lower').GetEntries() != y.Get('choice_tunep_lower').GetBinContent(2):
            for b,n in enumerate(['Global','TkOnly','TPFMS','Picky','DYT']):
                y.Get('choice_tunep_upper').GetXaxis().SetBinLabel(b+1,n)
            ROOT.gStyle.SetOptStat(0)
            y.Get('choice_tunep_upper').Draw('hist text00')
            y.Get('choice_tunep_lower').SetLineColor(ROOT.kRed)
            y.Get('choice_tunep_lower').Draw('hist text00 sames')
            leg = ROOT.TLegend( 0.78, 0.50, 0.98, 0.65 ) ; 
            leg.AddEntry( y.Get('choice_tunep_upper'), "upper" )
            leg.AddEntry( y.Get('choice_tunep_lower'), "lower" )
            if x == 'pT150200':
                leg.Draw()
            ps.save('choice_tunep_'+x, log=True)
        if y.Get('choice_tunep_old_upper').GetEntries() != y.Get('choice_tunep_old_upper').GetBinContent(2) or y.Get('choice_tunep_old_lower').GetEntries() != y.Get('choice_tunep_old_lower').GetBinContent(2):
            for b,n in enumerate(['Global','TkOnly','TPFMS','Picky','DYT']):
                y.Get('choice_tunep_old_upper').GetXaxis().SetBinLabel(b+1,n)
            ROOT.gStyle.SetOptStat(0)
            y.Get('choice_tunep_old_upper').Draw('hist text00')
            y.Get('choice_tunep_old_lower').SetLineColor(ROOT.kRed)
            y.Get('choice_tunep_old_lower').Draw('hist text00 sames')
            leg = ROOT.TLegend( 0.78, 0.50, 0.98, 0.65 ) ; 
            leg.AddEntry( y.Get('choice_tunep_old_upper'), "upper" )
            leg.AddEntry( y.Get('choice_tunep_old_lower'), "lower" )
            if x == 'pT150200':
                leg.Draw()
            ps.save('choice_tunep_old_'+x, log=True)

    for proj in ['xy', 'rz']:
        for which in ['upper', 'lower']:
            for end in ['inner', 'outer']:
                n = 'h_global_%s_%s_pos_%s' % (which, end, proj)
                h = drawer.file.histos.Get(n)
                h.SetStats(0)
                h.SetMarkerStyle(6)
                h.Draw()
                ps.save(n)

    ps.save_dir('upperR1lower')
    ps.save_dir('upperPlower')

    ps.make_canvas((700,700))
    ps.c.SetLogx(1)

    tracks = ['Global', 'TkOnly', 'TPFMS', 'Picky', 'DYT', 'OldTuneP', 'TuneP']

    curves = drawer.overlay_curves(tracks, 'qinvpt', 'upperR1lower', 'out', 0, 60)
    drawer.draw_legend((0.61,0.70,0.91,0.91), tracks)
    ps.save('res_out')

    curves = drawer.overlay_curves(tracks, 'qinvpt', 'upperR1lower', 'rms', 0, 0.2)
    drawer.draw_legend((0.21,0.70,0.49,0.91), tracks)
    ps.save('res_rms')

    curves = drawer.overlay_curves(tracks, 'qinvpt', 'upperR1lower', 'sigma', 0, 0.15)
    drawer.draw_legend((0.21,0.70,0.49,0.91), tracks)
    ps.save('res_sigma')

    curves = drawer.overlay_curves(tracks, 'qinvpt', 'upperR1lower', 'mean', -0.02, 0.03)
    drawer.draw_legend((0.21,0.70,0.49,0.91), tracks)
    ps.save('res_mean')

    curves = drawer.overlay_curves(tracks, 'qinvpt', 'upperPlower',  'sigma', 0.6, 1.8)
    drawer.draw_legend((0.21,0.70,0.49,0.91), tracks)
    ps.save('pull_sigma')

    curves = drawer.overlay_curves(tracks, 'qinvpt', 'upperPlower',  'mean', -0.6, 0.6)
    drawer.draw_legend((0.21,0.70,0.49,0.91), tracks)
    ps.save('pull_mean')

    print
