<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "DTD/xhtml1-transitional.dtd">
<html lang="de-DE">
 <head>
    <link href="/static/2d8248de8c9f2621ed0cd8f882266d95.css" rel="stylesheet" type="text/css" />  <link type="image/x-icon" href="/themes/default/graphics/favicon.ico" rel="SHORTCUT ICON" />    <title>Horde :: Anmelden</title>
 </head>

 <body class="modal-form">
<div class="modal-form">

<ul class="notices"><li><img alt="Nachricht" src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABQAAAAUCAQAAAAngNWGAAAAAXNSR0IArs4c6QAAAAJiS0dEAP+Hj8y/AAAACXBIWXMAAAmJAAAJiQGj0g7qAAAAB3RJTUUH3AcEDC8DFmWtAAAAAeZJREFUKM+V0ktoE0EYwPH/ZCfJJpsl0ZBGEaUpEhIoVWlqERGl4EGwV2+RoEcVD/WgiIeCIoI3L4IIYi5CpRelZ0GK2GwRvBSCScVEwbc2bZrHrushszaVHnRuM/Pjm/ke8I9L9G9Supv3j/lGSVP+tdgtieJyawuYzmkPg1k/Eg0Hmy7tJed02erdah7LnAs8jiZDRAhjECCAJJhwzmz/9qXUFzGb019EpMREo2PvtFbC6yOCBjarduvQkgU+gGFdFiMyRAyJQ7tyr36jvoIkRoiIlMVhXUFfwcxIDBW+Gc8+KDzvPWcgMTO+goIDExITAbQxSqde7RuPZ71cTSQDEwo2s0EkAB0ylYuzjz5Mf/SSlARpZhV0B+WfIs0N7UXcnZvdKJvEHVTQqG1AcXDb+c09kRg1BZN1Wx3qmBjaZmiTrCuYqnnQYc/89DKc+H7VWnvrKJjyIk4tuNUe7bLjzdHrcODd8WvaJwewcatTC6ozrv7yyZVjMSlo8LXSsBwgQHQyEfbzw775bHxStFQL3dyd208PG3KVNbxvBIjRsU/OX7gkLFT5EJY7cyR+ORwa8vel0a3eau6fEdZfY+bmWveLP1/zPmHvlrVdn0fIR/WzwtpicF2dPGOMkqbMIiWKosX/rt/EK5hZkgadpgAAAABJRU5ErkJggg==" />Ihr Browser hat sich anscheinend geändert, seit Sie die Sitzung begonnen haben. Zu Ihrer Sicherheit müssen Sie sich neu anmelden.</li></ul>
<form name="horde_login" id="horde_login" method="post" action="https://mail.tu-chemnitz.de/login.php">
 <input type="hidden" name="app" id="app" value="imp" />
 <input type="hidden" name="login_post" id="login_post" value="0" />
 <input type="hidden" name="url" value="https://mail.tu-chemnitz.de/imp/message.php?mailbox=aW1wc2VhcmNoAGRDWS1YYWk2djZRUEhhR1dpSlVEQXcx&amp;uid=356&amp;thismailbox=SU5CT1g" />
 <input type="hidden" name="anchor_string" id="anchor_string" value="" />

<div><label for="horde_user">Benutzername</label></div>
<div>
       <input type="text" autocapitalize="off" autocorrect="off" id="horde_user" name="horde_user" value="" style="direction:ltr" />
</div>
<div><label for="horde_pass">Passwort</label></div>
<div>
       <input type="password" id="horde_pass" name="horde_pass" value="" style="direction:ltr" />
</div>
<div><label for="horde_select_view">Modus</label></div>
<div>
       <select id="horde_select_view" name="horde_select_view">
        <option value="auto" selected="selected">Automatisch</option>
        <option value="" disabled="disabled">- - - - - - - - - -</option>
        <option value="basic">Einfach</option>
        <option value="dynamic" style="display:none">Dynamisch</option>
        <option value="smartmobile" style="display:none">Mobil (Smartphone)</option>
        <option value="mobile">Mobil (Minimal)</option>
       </select>
</div>

<div><label for="new_lang">Sprache</label></div>
<div><select id="new_lang" name="new_lang">
        <option value="ar_OM">&#x202d;Arabic (Oman) &#x202e;(عربية)</option>
        <option value="ar_SY">&#x202d;Arabic (Syria) &#x202e;(عربية)</option>
        <option value="id_ID">Bahasa Indonesia</option>
        <option value="bs_BA">Bosanski</option>
        <option value="bg_BG">&#x202d;Bulgarian (Български)</option>
        <option value="ca_ES">Català</option>
        <option value="cs_CZ">Český</option>
        <option value="zh_CN">&#x202d;Chinese (Simplified) (简体中文)</option>
        <option value="zh_TW">&#x202d;Chinese (Traditional) (正體中文)</option>
        <option value="da_DK">Dansk</option>
        <option value="de_DE" selected="selected">Deutsch</option>
        <option value="en_US">&#x202d;English (American)</option>
        <option value="en_GB">&#x202d;English (British)</option>
        <option value="en_CA">&#x202d;English (Canadian)</option>
        <option value="es_ES">Español</option>
        <option value="et_EE">Eesti</option>
        <option value="eu_ES">Euskara</option>
        <option value="fa_IR">&#x202d;Farsi (Persian) &#x202e;(فارسی)</option>
        <option value="fr_FR">Français</option>
        <option value="gl_ES">Galego</option>
        <option value="el_GR">&#x202d;Greek (Ελληνικά)</option>
        <option value="he_IL">&#x202d;Hebrew &#x202e;(עברית)</option>
        <option value="hr_HR">Hrvatski</option>
        <option value="is_IS">Íslenska</option>
        <option value="it_IT">Italiano</option>
        <option value="ja_JP">&#x202d;Japanese (日本語)</option>
        <option value="km_KH">&#x202d;Khmer (ខមែរ)</option>
        <option value="ko_KR">&#x202d;Korean (한국어)</option>
        <option value="lv_LV">Latviešu</option>
        <option value="lt_LT">Lietuvių</option>
        <option value="mk_MK">&#x202d;Macedonian (Македонски)</option>
        <option value="hu_HU">Magyar</option>
        <option value="nl_NL">Nederlands</option>
        <option value="nb_NO">&#x202d;Norsk (bokmål)</option>
        <option value="nn_NO">&#x202d;Norsk (nynorsk)</option>
        <option value="pl_PL">Polski</option>
        <option value="pt_PT">Português</option>
        <option value="pt_BR">Português do Brasil</option>
        <option value="ro_RO">Română</option>
        <option value="ru_RU">&#x202d;Russian (Русский)</option>
        <option value="sk_SK">Slovenský</option>
        <option value="sl_SI">Slovensko</option>
        <option value="fi_FI">Suomi</option>
        <option value="sv_SE">Svenska</option>
        <option value="th_TH">&#x202d;Thai (ภาษาไทย)</option>
        <option value="uk_UA">&#x202d;Ukrainian (Українська)</option>
</select></div>

<div>
 <input id="login-button" name="login_button" class="horde-default submit-button" value="Anmelden" type="submit" />
</div>



</form>
</div>

<script language="javascript">
document.title = 'TU Chemnitz: Webmail: Anmelden';
</script>

<div style="position:absolute;top:0;left:0;width:100%">
 <div style="margin:0 auto;width:60em;background-color:#177665;color:#fff;height:50px">
  <div style="height:50px;white-space:nowrap;float:left;">
 <a href="https://www.tu-chemnitz.de/"><img src="https://www.tu-chemnitz.de/tucal/img/logo.png" alt="TU-Logo" height="50" /></a></div>
  <div style="float:left;margin:10px 2em;vertical-align:bottom">
  <h1>Willkommen bei Webmail!</h1>
  </div>
 </div>
</div>
<div style="width:35em; margin:-2em auto;font-size:120%;ext-align:center">
 <div style="text-align:center;width:30em;border:4px dotted red; padding:1em 2em">
 <strong>Dies ist die neue Webmail-Version Horde5/IMP6!</strong><br />
 <a href="http://www.tu-chemnitz.de/urz/mail/imp/">Informieren Sie sich über
 <strong>neue Funktionen</strong> und <br />
 lesen Sie <strong>Hinweise zur Bedienung!</strong></a><br />
 Fragen bitte an den <a href="mailto:support@hrz.tu-chemnitz.de"><b>URZ-Helpdesk</b></a>.
 </div>
<!--
 <div style="text-align:center;margin:1em auto">
  <a href="http://www.tu-chemnitz.de/urz/mail/imp/">Hinweise zu Webmail</a> mit
  <a href="http://www.tu-chemnitz.de/urz/mail/imp/faq.html">Antworten auf häufig gestellte Fragen</a>
  </div>
-->

 <iframe scrolling="no" style="width:422px;height:77px;margin:1em 2em;padding:0px;background-color:#fff;" frameborder="0" src="https://www.tu-chemnitz.de/urz/tools/info.php" width="425" height="80"></iframe>

 <div style="width:30em; margin:1em auto">
    <ul>
     <li>Dieser Service erfordert Cookies, bitte überprüfen Sie Ihren Browser dahingehend.</li>
     <li>Aus Sicherheitsgründen zum Beenden auf <span style="width: 20px; height: 25px; margin: 0 10px 0 0;
          padding-left:11px; font-size:140%;
          background-image: url(themes/default/graphics/logout.png); background-color:black;
          background-repeat: no-repeat;">&nbsp; </span> klicken (Abmelden rechts oben).</li>
     <li>Ihre Fragen senden Sie bitte an den <a href="mailto:support@hrz.tu-chemnitz.de">URZ-Helpdesk.</a></li>
    </ul>
 </div>

<div style="margin:2em auto;eight:70px;vertical-align:middle;">
 <div style="float:left">
  <a href="http://login.tu-chemnitz.de/ssh.html" title="Starte Secure Shell-Verbindung"><img 
    src="/pics/term.png" alt="Starte Secure Shell-Verbindung" width="52" height="52" border="0"></a>
  <a href="https://login.tu-chemnitz.de/wfm/" title="Zugriff auf Dateien"><img
    src="/pics/wfm.png" alt="Zugriff auf Dateien" width="52" height="52" border="0"></a>
 </div>
 <div style="margin:0.5em 1em 1em 1em;float:left;vertical-align:middle">
  <a href="http://www.tu-chemnitz.de/urz/mail/">E-Mail an der TU Chemnitz</a><br />
  <a href="https://www.tu-chemnitz.de/urz/mail/log/"
    title="&Uuml;bersicht &uuml;ber Ihre gesendeten, empfangenen und abgewiesenen E-Mails">E-Mail-Protokolle</a><br />
  </div>
  <div style="float:left; margin:0.5em 1em 1em 1em;">
   <img src="/themes/default/graphics/horde-power1.png" alt="Powered by Horde" />
  </div>
 
 </div>
</div>
<!--
<table width="100%"><tr><td align="center"><img src="/themes/default/graphics/horde-power1.png" alt="Powered by Horde" /></td></tr></table>
-->

  <script type="text/javascript" src="/static/0a56d8870c0dfab8819c3663eee106a2ae450242.js"></script><script type="text/javascript" src="/static/63ccb953f74f53170b2a11f8a6de4a514048d43d.js"></script>  <script type="text/javascript">//<![CDATA[
HordeLogin.user_error="Bitte geben Sie einen Benutzernamen ein.";HordeLogin.pass_error="Bitte geben Sie ein Passwort ein.";HordeLogin.pre_sel="auto";ImpLogin.server_key_error="W\u00e4hlen Sie einen E-Mail-Server";
//]]></script>
 </body>
</html>
